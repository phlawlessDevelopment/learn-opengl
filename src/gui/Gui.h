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
        // FrameBuffer m_FrameBuffer;
    public:
        ImVec2 m_SceneSize;
        Gui(GLFWwindow* window);
        ~Gui();
        void Begin();
        void End();
        void Update(FrameBuffer& fb, std::vector<glm::vec3*>& transforms);

};