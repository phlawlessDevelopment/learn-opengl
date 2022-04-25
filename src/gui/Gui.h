#include <GLFW/glfw3.h>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

class GUI
{
    private:
        GLFWwindow* m_window;
        float* m_translationA;
        float* m_translationB;
        int m_Width, m_Height;
        void ResizeUI();
    public:
        GUI(GLFWwindow* window, float* translationA,float* translationB);
        ~GUI();
        void Render();
};