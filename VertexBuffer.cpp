#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glVerify(glGenBuffers(1, &_Id));
	glVerify(glBindBuffer(GL_ARRAY_BUFFER, _Id));
	glVerify(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}


VertexBuffer::~VertexBuffer()
{
	glVerify(glDeleteBuffers(1, &_Id));
}

void VertexBuffer::bind() const
{
	glVerify(glBindBuffer(GL_ARRAY_BUFFER, _Id));
}

void VertexBuffer::unbind() const
{
	glVerify(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
