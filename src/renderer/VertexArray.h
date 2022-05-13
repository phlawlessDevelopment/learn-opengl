#pragma once
#include <memory>
#include <vector>
#include "Buffer.h"

class VertexArray
{
    private:
        unsigned int m_RendererID;

    public:
        VertexArray();
        ~VertexArray();
      
        void Bind() const;
        void Unbind() const;
       
        void LinkVertexBuffer(VertexBuffer& vb);

};