#include "Buffer.h"
#include <GLFW/glfw3.h>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

class Gui
{
    private:
        GLFWwindow* m_window;
        ImVec2 m_SceneSize;
        std::shared_ptr<FrameBuffer> m_FrameBuffer;
        void ResizeUI();
        void CalculateSceneSize();
    public:
        Gui(GLFWwindow* window, std::shared_ptr<FrameBuffer>& fb);
        ~Gui();
        void Begin();
        void End();
        void Update();

};