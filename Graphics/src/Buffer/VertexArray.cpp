#include "pch.h"
#include "VertexArray.h"

VertexArray::VertexArray()
	: id()
{
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

// Gets the stride of a vertex buffer from its attributes.
unsigned int VertexArray::getStride(const std::vector<VertexAttrib>& attribs)
{
	// adds the size of each vertex attribute to 'stride'
	unsigned int stride = 0;
	for (const VertexAttrib& attrib : attribs)
		stride += attrib.count * DataMap::dataSizes[(int)attrib.type];
	return stride;
}

// Sequentially sets a vertex buffer's attributes (beginning at 'start').
// 'attribs' is a vector containing the 'count' and 'type' of each attribute's data (as a 'VertexAttrib' struct).
void VertexArray::AddVertexBuffer(const unsigned int start, const Buffer& vb, const std::vector<VertexAttrib>& attribs) const
{
	bind();
	vb.bind();

	unsigned int stride = getStride(attribs);
	unsigned int offset = 0;
	unsigned int idx = start;
	for (const VertexAttrib& attrib : attribs)
	{
		glEnableVertexAttribArray(idx);
		int dataIdx = (int)attrib.type;
		glVertexAttribPointer(idx++, attrib.count, DataMap::dataEnums[dataIdx],
			DataMap::dataNorm[dataIdx], stride, (const void*)offset);
		offset += attrib.count * DataMap::dataSizes[dataIdx];
	}

	unbind();
	vb.unbind();
}

// Sets the element buffer.
void VertexArray::SetElementBuffer(const Buffer& eb) const
{
	bind();
	eb.bind();
	unbind();
	eb.unbind();
}

// Binds the vertex array.
void VertexArray::bind() const
{
	glBindVertexArray(id);
}

// Unbinds the vertex array.
void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
