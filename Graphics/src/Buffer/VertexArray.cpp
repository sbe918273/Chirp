#include "pch.h"
#include "VertexArray.h"

VertexArray::VertexArray()
	: id()
{
	glGenVertexArrays(1, &id);
}

unsigned int VertexArray::getStride(const std::vector<VertexAttrib>& attribs)
{
	unsigned int stride = 0;
	for (const VertexAttrib& attrib : attribs)
		stride += attrib.count * DataMap::dataSizes[(int)attrib.type];
	return stride;
}

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

void VertexArray::SetElementBuffer(const Buffer& eb) const
{
	bind();
	eb.bind();
	unbind();
	eb.unbind();
}

void VertexArray::bind() const
{
	glBindVertexArray(id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
