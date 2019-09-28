#include "Renderer.h"
#include <iostream>

void glClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glLogError(const char* functionName, const char* filename, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGl Error] " << std::endl <<
			"in function: " << functionName << std::endl <<
			"in file: " << filename << std::endl <<
			"in line: " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::clear()
{
	glVerify(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
{
	shader.bind();
	vertexArray.bind();
	indexBuffer.bind();
	glVerify(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}
