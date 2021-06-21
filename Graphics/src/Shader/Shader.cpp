#include "pch.h"
#include "Shader.h"

Shader::Shader()
{}

Shader::Shader(const unsigned int typeCount, const std::vector<std::string>* fileNames, const ShaderMap::ShaderType* types)
{
	createProgram(typeCount, fileNames, types, id);
}

bool Shader::appendFileText(const std::string& fileName, std::string& outSource)
{
	std::string temp;
	std::ifstream inFile;
	inFile.open(fileName);
	if (inFile.is_open())
	{
		while (std::getline(inFile, temp))
			outSource += temp + "\n";
		inFile.close();
		return true;
	}

	std::cerr << "[Error: Shader:appendFileText] Could not open " << fileName << "." << std::endl;
	return false;
}

bool Shader::createShader(const ShaderMap::ShaderType type, const std::vector<std::string>& fileNames, GLuint& outShader)
{
	using namespace ShaderMap;

	std::string source = "";
	for (const std::string& fileName : fileNames)
	{
		if (!appendFileText(fileName, source))
		{
			std::cerr << "[Error: Shader::createShader] Could not open \"" << fileName << "\" "
				<< typeStrings[(int)type] << " shader source file." << std::endl;
			return false;
		}
	}

	// Create shader object and compile its source.
	outShader = glCreateShader(typeEnums[(int)type]);
	const GLchar* sourceString = source.c_str();
	glShaderSource(outShader, 1, &sourceString, nullptr);
	glCompileShader(outShader);

	// Check for shader compilation error.
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

bool Shader::createProgram(const unsigned int typeCount, const std::vector<std::string>* fileNames, const ShaderMap::ShaderType* types, GLuint& outProgram)
{
	outProgram = glCreateProgram();
	GLuint* shaders = new GLuint[typeCount];
	for (unsigned int i = 0; i < typeCount; i++)
	{
		if (!createShader(types[i], fileNames[i], shaders[i]))
		{
			std::cerr << "[Error: Shader::createProgram] Could not create " <<
				ShaderMap::typeStrings[(int)types[i]] << " shader." << std::endl;
			return false;
		}
		glAttachShader(outProgram, shaders[i]);
	}

	// link shaders.
	glLinkProgram(outProgram);

	// Check for linking errors.
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
	glUseProgram(0);

	for (unsigned int i = 0; i < typeCount; i++)
		glDeleteShader(shaders[i]);

	delete[] shaders;
	return true;
}