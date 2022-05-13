#pragma once
#include <memory>
#include <vector>
#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"


class Renderer
{
    private:
        std::shared_ptr<FrameBuffer> m_FrameBuffer;
    public:
        Renderer();
        ~Renderer();

        void BeginScene();
        
        void EndScene();
        void Flush();

        void Clear() const;
        void ClearColor(const glm::vec4& color) const;
        void Draw(const VertexArray& va);

};