#include <iostream>
#include <GL/glew.h>
#include "Renderer.h"

Renderer::Renderer()
 		 :m_RenderSets()
{

}
Renderer::~Renderer()
{

}
void Renderer::AddRenderSet(RenderSet& rs)
{
	m_RenderSets.push_back(rs);
}
void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw() const
{		
		glClearColor(0.2f,0.2f,0.4f,1.0f);

		static unsigned int count = m_RenderSets.size();
		for (int i = 0; i < count; i++)
		{
		RenderSet rs = m_RenderSets[i];
        rs.shader.Bind();
		rs.va.Bind();
		rs.ib.Bind();
		glDrawElements(GL_TRIANGLES,rs.ib.GetCount(),GL_UNSIGNED_INT,nullptr);
		}
		
}