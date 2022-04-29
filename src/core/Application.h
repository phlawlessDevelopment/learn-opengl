#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "helpers.h"
#include "gui/Gui.h"
#include "renderer/Renderer.h"

#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"



class Application
{   
    private:
        Renderer m_Renderer;
        Gui m_Gui;
        GLFWwindow* m_Window;
        int m_Width, m_Height, m_SceneWidth, m_SceneHeight;
        OrthographicCamera m_Camera;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<FrameBuffer> m_FrameBuffer;
        Shader m_Shader;
    public:
        Application();
        // Application(Application& a);
        ~Application();
        void Run();

};