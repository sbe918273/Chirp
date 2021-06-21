#include "pch.h"
#include "Shader.h"

Shader::Shader()
	: id()
{}

Shader::Shader(Shader&& other) noexcept
	: id(other.id)
{}

Shader& Shader::operator=(Shader&& other) noexcept
{
	id = other.id;
	return *this;
}

Shader::Shader(const unsigned int typeCount, const std::vector<std::string>* paths, const ShaderMap::ShaderType* types)
{
	createProgram(typeCount, paths, types, id);
}

// Sets the shader's id to OpenGL's active program.
void Shader::use() const
{
	glUseProgram(id);
}

// Appends a file's content to 'outString'. Returns success.
bool Shader::appendFileText(const std::string& path, std::string& outString)
{
	std::string temp;
	std::ifstream inFile;
	inFile.open(path);
	if (inFile.is_open())
	{
		while (std::getline(inFile, temp))
			outString += temp + "\n";
		inFile.close();
		return true;
	}

	std::cerr << "[Error: Shader:appendFileText] Could not open " << path << "." << std::endl;
	return false;
}

// Combines the content of files in 'paths' (in their given order) and compiles it into a shader at 'outShader'. Returns success.
bool Shader::createShader(const ShaderMap::ShaderType type, const std::vector<std::string>& paths, GLuint& outShader)
{
	using namespace ShaderMap;

	// combines contents of files in 'paths'
	std::string source = "";
	for (const std::string& path : paths)
	{
		if (!appendFileText(path, source))
		{
			std::cerr << "[Error: Shader::createShader] Could not open \"" << path << "\" "
				<< typeStrings[(int)type] << " shader source file." << std::endl;
			return false;
		}
	}

	// creates shader of given type and compiles its source
	outShader = glCreateShader(typeEnums[(int)type]);
	const GLchar* sourceString = source.c_str();
	glShaderSource(outShader, 1, &sourceString, nullptr);
	glCompileShader(outShader);

	// compilation error check
	GLint success;
	glGetShaderiv(outShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512] = {};
		glGetShaderInfoLog(outShader, 512, nullptr, infoLog);
		std::cerr << "[Error: Shader::createShader] Could not compile " << typeStrings[(int)type] << " shader." << std::endl;
		std::cerr << infoLog << std::endl;
		return false;
	}

	return true;
}

// Creates and combines shaders from their files in 'paths' into a program at 'outProgram'. Returns success.
// 'paths' is an array of vectors containing each shader's files (which are combined to make that shader in their given order).
// 'types' gives the shader type of each vector in 'paths'.
bool Shader::createProgram(const unsigned int typeCount, const std::vector<std::string>* paths, const ShaderMap::ShaderType* types, GLuint& outProgram)
{
	// creates program attaches created shaders.
	outProgram = glCreateProgram();
	GLuint* shaders = new GLuint[typeCount];
	for (unsigned int i = 0; i < typeCount; i++)
	{
		if (!createShader(types[i], paths[i], shaders[i]))
		{
			std::cerr << "[Error: Shader::createProgram] Could not create " <<
				ShaderMap::typeStrings[(int)types[i]] << " shader." << std::endl;
			return false;
		}
		glAttachShader(outProgram, shaders[i]);
	}
	glLinkProgram(outProgram);

	// linking error check.
	GLint success;
	glGetProgramiv(outProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512] = {};
		glGetProgramInfoLog(outProgram, 512, nullptr, infoLog);
		std::cerr << "[Error: Shader::createProgram] Could not link program." << std::endl;
		std::cerr << infoLog << std::endl;
		return false;
	}

	// delete shaders
	for (unsigned int i = 0; i < typeCount; i++)
		glDeleteShader(shaders[i]);

	delete[] shaders;
	return true;
}

