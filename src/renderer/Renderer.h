#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

struct RenderSet{
    VertexArray va;
    VertexBuffer vb;
    VertexBufferLayout layout;
    IndexBuffer ib;
    Shader shader;
};

class Renderer
{
    private:
        std::vector<RenderSet> m_RenderSets;
    public:
        Renderer();
        ~Renderer();
        void AddRenderSet(RenderSet& rs);

        void Clear() const;
        void Draw() const;
};