#pragma once
#include "VertexArray.h"
#include "Mesh.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
class Sprite
{
private:
    VertexArray m_VertexArray;
    glm::vec3 m_Position;
    
public:
    inline VertexArray GetVertexArray() {return m_VertexArray;} 
    inline glm::vec3& GetPosition() {return m_Position;}
    inline float* GetTransform() {return &m_Position.x;}
    void SetPostion(const glm::vec3 newPos);
    Sprite();
    ~Sprite();
};

Sprite::Sprite(/* args */)
: m_Position(0.0f,0.0f,0.0f)
{   
    VertexBufferLayout layout = VertexBufferLayout();

    const unsigned int positionsLength = QuadMesh::PosCount;
    const float* positions = QuadMesh::GetPositions();
    int indicesLength = QuadMesh::IndexCount;
    const unsigned int* indicies = QuadMesh::GetIndices();


    layout.Push<float>(2);
    layout.Push<float>(2);
    // layout.Push<float>(4);

    m_VertexArray = VertexArray();
	m_VertexArray.Bind();
	
    VertexBuffer* vb = new VertexBuffer(positions, positionsLength * sizeof(float));
    vb->SetLayout(layout);

    IndexBuffer* ib =  new IndexBuffer(indicies,indicesLength);
    m_VertexArray.LinkVertexBuffer(*vb);

	m_VertexArray.Unbind();
	vb->Unbind();
	ib->Unbind();
}

Sprite::~Sprite()
{
}

void Sprite::SetPostion(const glm::vec3 newPos){
    m_Position = newPos;
}