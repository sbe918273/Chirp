#include "pch.h"
#include <vector>
#include <fstream>
#include <string>

#include "ShaderMap.h"

class Shader
{
public:
	Shader();
	Shader(const unsigned int typeCount, const std::vector<std::string>* fileNames, const ShaderMap::ShaderType* types);
	static bool createProgram(const unsigned int typeCount, const std::vector<std::string>* fileNames, const ShaderMap::ShaderType* types, GLuint& outProgram);
private:
	GLuint id;
	static bool appendFileText(const std::string& fileName, std::string& outSource);
	static bool createShader(const ShaderMap::ShaderType type, const std::vector<std::string>& fileNames, GLuint& outShader);
};