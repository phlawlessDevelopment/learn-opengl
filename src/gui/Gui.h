#include <GLFW/glfw3.h>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

class Gui
{
    private:
        GLFWwindow* m_window;
        int m_Width, m_Height;
        void ResizeUI();
        void CalculateSceneSize();
    public:
        Gui(GLFWwindow* window);
        ~Gui();
        void Begin();
        void End();
        void Update(const int sceneWidth, const int sceneHeight, const unsigned int renderTexID);

};