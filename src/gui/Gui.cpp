#include <iostream>
#include "Gui.h"

Gui::Gui(GLFWwindow* window)
	:m_Width(0),m_Height(0),
	m_window(window)
{
	if(window == nullptr)
		return;
	glfwGetWindowSize(m_window, &m_Width, &m_Height);
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
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// GLFWwindow* backup_current_context = glfwGetCurrentContext();
	// ImGui::UpdatePlatformWindows();
	// ImGui::RenderPlatformWindowsDefault();
	// glfwMakeContextCurrent(backup_current_context);
}
void Gui::Update(const int sceneWidth, const int sceneHeight, const unsigned int renderTexID)
{
		ResizeUI();
		ImGuiID dock_id = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::SetNextWindowDockID(dock_id);
		ImVec2 windowSize = ImVec2(sceneWidth,sceneHeight);
		ImGui::SetNextWindowSize(windowSize);
		ImGui::Begin("Scene");
		// Because I use the texture from OpenGL, I need to invert the V from the UV.
		ImGui::Image((ImTextureID)renderTexID, windowSize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
		ImGui::Begin("Tree");
		ImGui::End();
		ImGui::Begin("Files");
		ImGui::End();
		ImGui::Begin("Tools");
		ImGui::End();
		ImGui::Begin("Props");
		ImGui::End();
		
}
void Gui::ResizeUI()
{
	glfwGetWindowSize(m_window, &m_Width, &m_Height);
}
