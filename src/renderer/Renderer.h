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
        
    public:
        Renderer();
        ~Renderer();

        void BeginScene();
        void Submit(const std::shared_ptr<VertexArray>& va);
        void EndScene();
        void Flush();

        void Clear() const;
        void ClearColor(const glm::vec4& color) const;
        void DrawIndexed(const std::shared_ptr<VertexArray>& va);

};