#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"



int main()
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // tells glfw to use modern opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // opengl 4.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // opengl 4.6

	if(!glfwInit()){
		return -1;
	}
	
	GLFWwindow* window = glfwCreateWindow(640, 480, "phlawlessEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if(glewInit()!= GLEW_OK){
		std::cout << "Failed to init GLEW " << std::endl;
	}
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window,true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	

	const unsigned int positionsLength = 16;
	float positions[positionsLength]= {
		100.0f, 100.0f, 0.0f, 0.0f,
		200.0f, 100.0f, 1.0f, 0.0f,
		200.0f, 200.0f, 1.0f, 1.0f,
     	100.0f, 200.0f, 0.0f, 1.0f
	};
	unsigned int indicies[]={
		0,1,2,
		2,3,0
	};

	// default blend settings
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;

	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb,layout);
	IndexBuffer ib(indicies,6);

	// 4x3
	glm::mat4 projection = glm::ortho(0.0f,640.0f,0.0f,480.0f,-1.0f,1.0f);
	// "camera" movement
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100,0,0));
	// object movement
	glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(200,200,0));
	//opengl expects these in "reverse" order
	glm::mat4 MVP = projection * view * model;

	Shader shader("../shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color",0.2f,0.2f,0.4f,1.0f);
	shader.SetUniformMat4f("u_ModelViewProjection",MVP);
	
	Texture texture("../res/textures/dice.png");
	texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);
	
	Renderer renderer;


	while (!glfwWindowShouldClose(window))
	{	

		renderer.Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();



		glClearColor(0.2f,0.2f,0.4f,1.0f);
		renderer.Draw(va,ib,shader);	

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	ImGui_ImplGlfw_Shutdown();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}