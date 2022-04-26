#pragma once

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