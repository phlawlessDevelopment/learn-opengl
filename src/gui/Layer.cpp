#include "Layer.h"

Layer::Layer()
{

}
Layer:: ~Layer()
{

}

void Layer::OnAttach()
{

}
void Layer::OnDetach()
{

}
void Layer::OnRender()
{

}
void Layer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void Layer::End()
{
    ImGuiIO& io = ImGui::GetIO();
    
}