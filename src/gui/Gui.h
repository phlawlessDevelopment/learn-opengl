#include <GLFW/glfw3.h>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
class GUI
{
    private:
        GLFWwindow* m_window;
        int m_Width, m_Height;
        ImVec2 m_VDockSize, m_HDockSize;
        ImVec2 m_LDockPos , m_RDockPos, m_TDockPos, m_BDockPos;
        void ResizeDocks();
    public:
        GUI(GLFWwindow* window);
        ~GUI();
        void Render();
};