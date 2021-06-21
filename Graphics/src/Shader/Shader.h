#include "pch.h"
#include <vector>
#include <fstream>
#include <string>

#include "ShaderMap.h"

class Shader
{
public:
	Shader();
	Shader(const Shader& other) = delete;
	Shader(Shader&& other) noexcept;
	Shader& operator=(const Shader& other) = delete;
	Shader& operator=(Shader&& other) noexcept;
	Shader(const unsigned int typeCount, const std::vector<std::string>* paths, const ShaderMap::ShaderType* types);

	void use() const;
	static bool createProgram(const unsigned int typeCount, const std::vector<std::string>* paths, const ShaderMap::ShaderType* types, GLuint& outProgram);
private:
	GLuint id;
	static bool appendFileText(const std::string& path, std::string& outSource);
	static bool createShader(const ShaderMap::ShaderType type, const std::vector<std::string>& paths, GLuint& outShader);
};