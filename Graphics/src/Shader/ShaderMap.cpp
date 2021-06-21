#include "pch.h"
#include "ShaderMap.h"

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