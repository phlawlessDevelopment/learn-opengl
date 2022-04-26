#pragma once
#include "VertexBufferLayout.h"

class VertexBuffer
{
    private:
        unsigned int m_RedererID;
        std::shared_ptr<VertexBufferLayout> m_Layout;

    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();
    
        void Bind() const;
        void Unbind() const;
        inline std::shared_ptr<VertexBufferLayout>GetLayout(){return m_Layout;}
        static inline VertexBuffer* Create(const void* data, unsigned int size)
        {
            return new VertexBuffer(data,size);
        } 

};