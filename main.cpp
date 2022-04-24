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
	const unsigned int positionsLength = 16;
	float positions[positionsLength]= {
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
     	-0.5f, 0.5f, 0.0f, 1.0f
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
	// glm::mat4 projectionMatrix = glm::ortho(-2.0f,2.0f,-1.5f,1.5f,-1.0f,1.0f);
	// no change
	glm::mat4 projectionMatrix = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f);

	Shader shader("../shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color",0.2f,0.2f,0.4f,1.0f);
	shader.SetUniformMat4f("u_ModelViewProjection",projectionMatrix);
	
	Texture texture("../res/textures/dice.png");
	texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);
	
	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{	

		renderer.Clear();
		glClearColor(0.2f,0.2f,0.4f,1.0f);
		renderer.Draw(va,ib,shader);	

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}