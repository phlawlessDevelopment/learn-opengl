#pragma once
#include <memory>
#include <vector>
#include "Buffer.h"

class VertexArray
{
    private:
        unsigned int m_RendererID;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;

    public:
        VertexArray();
        ~VertexArray();
      
        void Bind() const;
        void Unbind() const;
       
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib);
      
        inline std::shared_ptr<IndexBuffer> GetIndexBuffer(){return m_IndexBuffer;}
        static inline VertexArray* Create()
        {
            return new VertexArray();
        } 
};