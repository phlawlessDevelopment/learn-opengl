#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
    private:
        unsigned int m_RendererID;
        IndexBuffer m_IndexBuffer;

    public:
        VertexArray(const IndexBuffer& ib);
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;
        inline IndexBuffer GetIndexBuffer(){return m_IndexBuffer;}
};