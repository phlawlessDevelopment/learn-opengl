#include <iostream>
#include <memory>
#include "Gui.h"

Gui::Gui(GLFWwindow* window)
	:m_window(window)
{
	// glfwGetWindowSize(m_window, &m_Width, &m_Height);
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	ImGui::StyleColorsDark();	
	
	}
Gui::~Gui()
{

}
void Gui::Begin()
{
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplGlfw_NewFrame();
ImGui::NewFrame();
}
void Gui::End()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void Gui::Update(FrameBuffer& fb,std::vector<glm::vec3*> & transforms)
{	
		ImGuiID dock_id = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::SetNextWindowDockID(dock_id);
		ImGui::Begin("Scene");
		ImVec2 sceneSize = ImGui::GetWindowSize();
		if(sceneSize.x != m_SceneSize.x || sceneSize.y != m_SceneSize.y)
		{
			// std::cout << sceneSize.x <<" , " << sceneSize.y << std::endl;
			fb.Invalidate(sceneSize.x,sceneSize.y);
		}
		m_SceneSize = sceneSize;
		ImGui::Image((void*)fb.GetColorAttachment(), ImGui::GetWindowSize());
		ImGui::End();
		ImGui::Begin("Tree");
		ImGui::End();
		ImGui::Begin("Files");
		ImGui::End();
		ImGui::Begin("Tools");
		ImGui::End();
		ImGui::Begin("Props");
		for (int i = 0; i < transforms.size(); i++)
		{
			// std::cout << "(" << transforms[i]->x <<"," <<transforms[i]->y<<"," <<transforms[i]->z<<")"<<std::endl;
			ImGui::PushID(i);
			ImGui::InputFloat3("sprite " + i, &transforms[i]->x);
			ImGui::PopID();
		}
		ImGui::End();
		
}

