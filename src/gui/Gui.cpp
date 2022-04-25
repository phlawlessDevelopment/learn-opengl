#include "Gui.h"

GUI::GUI(GLFWwindow* window, float* translationA, float* translationB)
	:m_Width(0),m_Height(0), m_translationA(nullptr), m_translationB(nullptr),
	m_window(window)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
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
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::Begin("win");
		ImGui::SliderFloat3("Translation A",m_translationA,-2.0f,2.0f);
		ImGui::End();
		ImGui::Begin("win 2");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void GUI::ResizeUI()
{
	glfwGetWindowSize(m_window, &m_Width, &m_Height);
}