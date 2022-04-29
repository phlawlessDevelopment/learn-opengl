#include <iostream>
#include "Buffer.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    :m_RedererID(0)
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

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height)
    :m_RedererID(0),m_RenderBuffer(0),m_ColorAttachemnt(0)
{
    Invalidate(width,height);
}
FrameBuffer::~FrameBuffer()
{

}
void FrameBuffer::Invalidate(uint32_t width, uint32_t height)
{
    glCreateFramebuffers(1, &m_RedererID);
    glBindFramebuffer(GL_FRAMEBUFFER,m_RedererID);

    glCreateTextures(GL_TEXTURE_2D,1,&m_ColorAttachemnt);
    glBindTexture(GL_TEXTURE_2D,m_ColorAttachemnt);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachemnt, 0);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "frame buffer error " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
}
void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER,m_RedererID);
}
void FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}