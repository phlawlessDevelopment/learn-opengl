#include "Buffer.h"

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

void VertexBuffer::SetLayout(const VertexBufferLayout& layout)
{
    m_Layout = layout;
}
void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RedererID);
}
void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)
{
   	glGenBuffers(1, &m_RedererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RedererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1,&m_RedererID);
}
    
void IndexBuffer::Bind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RedererID);
}
void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
