#pragma once
#include "pch.h"

namespace DataMap
{
	enum class DataType
	{
		FLOAT,
		UNSIGNED_INT,
		UNSIGNED_BYTE
	};

	extern const unsigned int dataSizes[3];
	extern const GLenum dataEnums[3];
	extern const bool dataNorm[3];
}
