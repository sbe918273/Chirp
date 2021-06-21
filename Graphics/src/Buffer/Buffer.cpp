#include "pch.h"
#include "Buffer.h"

Buffer::Buffer(const GLenum aType)
	: id(), type(aType)
{
	glGenBuffers(1, &id);
}

Buffer::Buffer(const GLenum aType, const unsigned int size, const GLenum mode, const void* data)
	: id(), type(aType)
{
	glGenBuffers(1, &id);
	setData(size, mode, data);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &id);
}

// Sets the buffer's data for the first time.
void Buffer::setData(const unsigned int size, const GLenum mode, const void* data) const
{
	bind();
	glBufferData(type, size, data, mode);
	unbind();
}

// Changes the buffer's data.
void Buffer::subData(const unsigned int size, const unsigned int offset, const void* data) const
{
	bind();
	glBufferSubData(type, offset, size, data);
	unbind();
}

// Binds the buffer.
void Buffer::bind() const
{
	glBindBuffer(type, id);
}

// Unbind the buffer.
void Buffer::unbind() const
{
	glBindBuffer(type, 0);
}

