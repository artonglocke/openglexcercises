#ifndef RENDERER_H
#define RENDERER_H

#include <Gl/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define Assert(func) if(!(func));

#define glVerify(func) glClearErrors(); \
		func;\
		Assert(glLogError(#func, __FILE__, __LINE__));

void glClearErrors();
bool glLogError(const char* functionName, const char* filename, int line);

class Renderer
{
public:
	void clear();
	void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
};

#endif // RENDERER_H