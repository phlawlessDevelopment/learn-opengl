#pragma once
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

class Layer
{
    public:
        Layer();
        ~Layer();

        void OnAttach();
        void OnDetach();
        void OnRender();
        void Begin();
        void End();

};