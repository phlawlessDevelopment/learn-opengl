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

FrameBuffer::FrameBuffer(const int width,const int height)
    :m_RedererID(0),m_RenderBuffer(0),m_RenderTexID(0)
{
    glGenFramebuffers(1,&m_RedererID);
    glBindFramebuffer(GL_FRAMEBUFFER,m_RedererID);

    glGenTextures(1, &m_RenderTexID);
    glBindTexture(GL_TEXTURE_2D, m_RenderTexID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderTexID, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glGenRenderbuffers(1, &m_RenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 640, 480);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "frame buffer error " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;

}
FrameBuffer::~FrameBuffer()
{

}
void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER,m_RedererID);
    glViewport(0,0,640,480);
}
void FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}