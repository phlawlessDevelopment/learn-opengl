#include <iostream>
#include <GL/glew.h>
#include "Renderer.h"


Renderer::Renderer()
{

}
Renderer::~Renderer()
{

}
void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void Renderer::ClearColor(const glm::vec4& color) const
{
	glClearColor(color.r,color.g,color.b,color.a);
}

void Renderer::BeginScene()
{

}
void Renderer::Draw(const VertexArray& va)
{
		va.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);
}
void Renderer::EndScene()
{
	
}
void Renderer::Flush()
{
	
}

