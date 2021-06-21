#pragma once
#include "Buffer.h"
#include "DataMap.h"

struct VertexAttrib
{
	const unsigned int count;
	const DataMap::DataType type;
};

class VertexArray
{
public:
	VertexArray();
	VertexArray(const VertexArray& other) = delete;
	VertexArray(VertexArray&& other) = delete;
	VertexArray& operator=(const VertexArray& other) = delete;
	VertexArray& operator=(VertexArray&& other) = delete;

	static unsigned int getStride(const std::vector<VertexAttrib>& attribs);

	void AddVertexBuffer(unsigned int start, const Buffer& vb, const std::vector<VertexAttrib>& attribs) const;
	void SetElementBuffer(const Buffer& eb) const;

	void bind() const;
	void unbind() const;
private:
	GLuint id;
};