#include "pch.h"
#include "DataMap.h"

const unsigned int DataMap::dataSizes[3] =
{
	4, 4, 1
};

const GLenum DataMap::dataEnums[3] =
{
	GL_FLOAT, GL_UNSIGNED_INT, GL_UNSIGNED_BYTE
};

const bool DataMap::dataNorm[3] =
{
	false, false, true
};