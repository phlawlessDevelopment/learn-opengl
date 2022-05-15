#pragma once
#include <memory>
#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch (type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0) {}
    
    template <typename T>
    void Push(unsigned int count)
    {
        // static_assert(false);
    }
    inline std::vector<VertexBufferElement> GetElements() const {return m_Elements;}
    inline unsigned int GetStride() const {return m_Stride;}
   
};

template <>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{   
    VertexBufferElement vbe = {GL_FLOAT,count,GL_FALSE};
    m_Elements.push_back(vbe);
    m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}
template <>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    VertexBufferElement vbe = {GL_UNSIGNED_INT,count,GL_FALSE};
    m_Elements.push_back(vbe);
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT)* count;
}
template <>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
   VertexBufferElement vbe = {GL_UNSIGNED_BYTE,count,GL_TRUE};
    m_Elements.push_back(vbe);
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE)* count;
}



class VertexBuffer
{
    private:
        unsigned int m_RedererID;
        VertexBufferLayout m_Layout;

    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();
    
        void Bind() const;
        void Unbind() const;
        void Delete() const;
        void SetLayout(const VertexBufferLayout& layout);
        inline VertexBufferLayout GetLayout(){return m_Layout;}

};

class IndexBuffer
{
    private:
        unsigned int m_RedererID;

    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();
    
    void Bind() const;
    void Unbind() const;
};

class FrameBuffer
{
    private:
        unsigned int m_RedererID;
        unsigned int m_ColorAttachemnt;
        unsigned int m_RenderBuffer;
        
    public:
        FrameBuffer(uint32_t width, uint32_t height);
        ~FrameBuffer();
    
    void Invalidate(uint32_t width, uint32_t height);
    void Bind() const;
    void Unbind() const;
    void Delete();

    inline unsigned int GetColorAttachment() const {return m_ColorAttachemnt;}
    static inline FrameBuffer* Create(const int width,const int height)
    {
        return new FrameBuffer(width,height);
    }
};