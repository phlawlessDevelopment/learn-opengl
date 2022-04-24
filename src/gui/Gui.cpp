#include "Gui.h"

GUI::GUI(GLFWwindow* window)
	:m_Width(0),m_Height(0),
	m_LDockPos(ImVec2(0,0)),
	m_RDockPos(ImVec2(0,0)),
	m_TDockPos(ImVec2(0,0)),
	m_BDockPos(ImVec2(0,0)),
	m_HDockSize(ImVec2(0,0)),
	m_VDockSize(ImVec2(0,0)),
	m_window(window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window,true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();	


}
GUI::~GUI()
{
    ImGui_ImplGlfw_Shutdown();
}
void GUI::Render()
{		
		ResizeDocks();
    	ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(m_LDockPos);
		ImGui::SetNextWindowSize(m_VDockSize);
		ImGui::Begin("Scene Tree");
		ImGui::End();

		ImGui::SetNextWindowPos(m_RDockPos);
		ImGui::SetNextWindowSize(m_VDockSize);
		ImGui::Begin("Properties");
		ImGui::End();

		ImGui::SetNextWindowPos(m_TDockPos);
		ImGui::SetNextWindowSize(m_HDockSize);
		ImGui::Begin("Tools");
		ImGui::End();

		ImGui::SetNextWindowPos(m_BDockPos);
		ImGui::SetNextWindowSize(m_HDockSize);
		ImGui::Begin("Files");
		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void GUI::ResizeDocks()
{
	glfwGetWindowSize(m_window, &m_Width, &m_Height);
	int vDockWidth = m_Width/5;
	int hDockHeight = m_Height/5;
	m_VDockSize = ImVec2(vDockWidth, m_Height);
	m_LDockPos = ImVec2(0,0);
	m_RDockPos = ImVec2(m_Width - vDockWidth,0);

	m_HDockSize =  ImVec2(m_Width - (vDockWidth)*2,hDockHeight);
	m_TDockPos = ImVec2(vDockWidth,0);
	m_BDockPos = ImVec2(vDockWidth,m_Height- hDockHeight);
}