#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"



int main()
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // tells glfw to use modern opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // opengl 4.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // opengl 4.6

	if(!glfwInit()){
		return -1;
	}
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "phlawlessEngine", NULL, NULL);
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
		-0.1f, -0.1f, 0.0f, 0.0f,
		0.1f, -0.1f, 1.0f, 0.0f,
		0.1f, 0.1f, 1.0f, 1.0f,
     	-0.1f, 0.1f, 0.0f, 1.0f
	};
	unsigned int indicies[]={
		0,1,2,
		2,3,0
	};
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;

	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb,layout);
	IndexBuffer ib(indicies,6);

	Shader shader("../shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);
	
	Texture texture("../res/textures/dice.png");
	texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);
	
	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{	

		renderer.Clear();
		glClearColor(0.8f, 0.3f, 0.8f, 1.0f);
		renderer.Draw(va,ib,shader);	

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}