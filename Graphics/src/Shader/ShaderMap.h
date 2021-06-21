#pragma once
#include "pch.h"

namespace ShaderMap
{
	enum class ShaderType
	{
		VERTEX,
		GEOMETRY,
		FRAGMENT
	};

	extern const GLenum typeEnums[3];
	extern const std::string typeStrings[3];
}
