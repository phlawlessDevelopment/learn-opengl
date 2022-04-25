#include "Gui.h"

GUI::GUI(GLFWwindow* window, float* translationA, float* translationB)
	:m_Width(0),m_Height(0), m_translationA(nullptr), m_translationB(nullptr),
	m_window(window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window,true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();	
	m_translationA = translationA;
	m_translationB = translationB;

}
GUI::~GUI()
{
    ImGui_ImplGlfw_Shutdown();
}
void GUI::Render()
{		
		ResizeUI();
    	ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SliderFloat3("Translation A",m_translationA,-2.0f,2.0f);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void GUI::ResizeUI()
{
	glfwGetWindowSize(m_window, &m_Width, &m_Height);
}