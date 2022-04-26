#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "gui/Gui.h"
#include "renderer/Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


class Application
{   
    private:
        Renderer m_Renderer;
        Gui m_Gui;
        GLFWwindow* m_Window;
        unsigned int m_Width, m_Height;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
    public:
        Application();
        ~Application();
        void Run();

};