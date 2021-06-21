#include "ShaderMap.h"

enum class ShaderMap::ShaderType
{
	VERTEX_SHADER,
	GEOMETRY_SHADER,
	FRAGMENT_SHADER
};

const GLenum ShaderMap::typeEnums[3] =
{
	GL_VERTEX_SHADER,
	GL_GEOMETRY_SHADER,
	GL_FRAGMENT_SHADER
};

const std::string ShaderMap::typeStrings[3] =
{
	"vertex",
	"geometry",
	"fragment"
};