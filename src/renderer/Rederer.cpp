#include <iostream>
#include <GL/glew.h>
#include "Renderer.h"

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
        shader.Bind();
		va.Bind();
		ib.Bind();
		glClearColor(0.2f,0.2f,0.4f,1.0f);
		glDrawElements(GL_TRIANGLES,ib.GetCount(),GL_UNSIGNED_INT,nullptr);
}