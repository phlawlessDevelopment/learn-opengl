#include "VertexArray.h"
VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1,&m_RendererID);
}
void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb)
{   
    glBindVertexArray(m_RendererID);
    vb -> Bind();

    const auto& layout = vb->GetLayout();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,element.count,element.type,element.normalized,layout.GetStride(),(const void*)offset);
        offset+=element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
    m_VertexBuffers.push_back(vb);
}
void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
{
    glBindVertexArray(m_RendererID);
    ib -> Bind();
    m_IndexBuffer = ib;

}
void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}