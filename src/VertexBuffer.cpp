#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RedererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RedererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&m_RedererID);
}
    
void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RedererID);
}
void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
