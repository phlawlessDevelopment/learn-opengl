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
#include "gui/Gui.h"




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

	

	const unsigned int positionsLength = 64;
	float positions[positionsLength]= {
		-1.5f, -0.5f, 0.0f, 0.0f, 0.18f, 0.6f,0.96f,1.0f,
		-0.5f, -0.5f, 1.0f, 0.0f, 0.18f, 0.6f,0.96f,1.0f,
		-0.5f, 0.5f, 1.0f, 1.0f, 0.18f, 0.6f,0.96f,1.0f,
     	-1.5f, 0.5f,0.0f, 1.0f, 0.18f, 0.6f,0.96f,1.0f,

		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.93f , 0.24f,1.0f,
		1.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.93f , 0.24f,1.0f,
		1.5f, 0.5f, 1.0f, 1.0f,1.0f, 0.93f , 0.24f,1.0f,
     	0.5f, 0.5f, 0.0f, 1.0f,1.0f, 0.93f , 0.24f,1.0f,

	};
	const unsigned int indicesLength = 12;
	unsigned int indicies[12]={
		0,1,2,2,3,0,
		4,5,6,6,7,4
	};

	// default blend settings
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	VertexArray va;
	VertexBuffer vb(positions, positionsLength * sizeof(float));
	VertexBufferLayout layout;

	layout.Push<float>(2);
	layout.Push<float>(2);
	layout.Push<float>(4);
	va.AddBuffer(vb,layout);
	IndexBuffer ib(indicies,indicesLength);
	
	// 4x3
	glm::mat4 projection = glm::ortho(-2.0f,2.0f,-1.5f,1.5f,-1.0f,1.0f);
	// "camera" movement
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
	// object movement


	Shader shader("../shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform<glm::vec4>("u_Color",glm::vec4(1.0f,1.0f,1.0f,1.0f));
	
	
	Texture texture("../res/textures/dice.png");
	texture.Bind(0);
	shader.SetUniform<int>("u_Texture", 0);
	
	Renderer renderer;
	glm::vec3 translationA = glm::vec3(0,0,0);
	glm::vec3 translationB = glm::vec3(400,200,0);
	GUI gui(window, &translationA.x,&translationB.x);

	while (!glfwWindowShouldClose(window))
	{	
		renderer.Clear();
		/*rendering */
		
		shader.Bind();
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f),translationA);
			glm::mat4 mvp = projection * view * model;
			shader.SetUniform<glm::mat4>("u_ModelViewProjection",mvp);
			renderer.Draw(va,ib,shader);
		}
		// {
		// 	glm::mat4 model = glm::translate(glm::mat4(1.0f),translationB);
		// 	glm::mat4 mvp = projection * view * model;
		// 	shader.SetUniform<glm::mat4>("u_ModelViewProjection",mvp);
		// 	renderer.Draw(va,ib,shader);
		// }
		

		gui.Render();	
		/*end rendering */
	
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}