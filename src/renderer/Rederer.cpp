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
void Renderer::Submit(const std::shared_ptr<VertexArray>& va ,std::shared_ptr<FrameBuffer> fb)
{	fb->Bind();
	DrawIndexed(va);
	fb->Unbind();
}
void Renderer::EndScene()
{
	
}
void Renderer::Flush()
{
	
}
void Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& va)
{		
		va->Bind();
		glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT,nullptr);
}
