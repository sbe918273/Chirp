#pragma once
#include "pch.h"
#include <vector>

class Buffer
{
public:
	Buffer(const GLenum aType);
	Buffer(const GLenum aType, const unsigned int size, const GLenum mode, const void* data);
	Buffer(const Buffer& other) = delete;
	Buffer(Buffer&& other) = delete;
	Buffer& operator=(const Buffer& other) = delete;
	Buffer& operator=(Buffer&& other) = delete;
	~Buffer();

	void setData(const unsigned int size, const GLenum mode, const void* data) const;
	void subData(const unsigned int size, const unsigned int offset, const void* data) const;
	void bind() const;
	void unbind() const;

protected:
	GLuint id;
	GLenum type;
};
