#include <GL/glew.h>
#include "IndexBuffer.h"
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
