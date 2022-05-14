#pragma once
#include "Buffer.h"
#include <GLFW/glfw3.h>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/glm/glm.hpp"

class Gui
{
    private:
        GLFWwindow* m_window;
        ImVec2 m_SceneSize;
        // FrameBuffer m_FrameBuffer;
        void ResizeUI();
        void CalculateSceneSize();
    public:
        Gui(GLFWwindow* window);
        ~Gui();
        void Begin();
        void End();
        void Update(FrameBuffer& fb, std::vector<float*>& transforms);

};