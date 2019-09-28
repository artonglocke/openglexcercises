#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: _count(count)
{
	glVerify(glGenBuffers(1, &_Id));
	glVerify(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Id));
	glVerify(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	glVerify(glDeleteBuffers(1, &_Id));
}

void IndexBuffer::bind() const
{
	glVerify(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Id));
}

void IndexBuffer::unbind() const
{
	glVerify(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
