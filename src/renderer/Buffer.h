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
        void SetLayout(const VertexBufferLayout& layout);
        inline VertexBufferLayout GetLayout(){return m_Layout;}
        static inline VertexBuffer* Create(const void* data, unsigned int size)
        {
            return new VertexBuffer(data,size);
        } 

};

class IndexBuffer
{
    private:
        unsigned int m_RedererID;
        unsigned int m_Count;

    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();
    
    void Bind() const;
    void Unbind() const;
    inline unsigned int GetCount() const {return m_Count;}
    static inline IndexBuffer* Create(const unsigned int* data, unsigned int count)
    {
        return new IndexBuffer(data,count);
    }
};

class FrameBuffer
{
    private:
        unsigned int m_RedererID;
        unsigned int m_RenderTexID;
        unsigned int m_RenderBuffer;
        
    public:
        FrameBuffer(const int width,const int height);
        ~FrameBuffer();
    
    void Bind() const;
    void Unbind() const;
    inline unsigned int GetRenderTexture() const {return m_RenderTexID;}
    static inline FrameBuffer* Create(const int width,const int height)
    {
        return new FrameBuffer(width,height);
    }
};