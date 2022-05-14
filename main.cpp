#include <iostream>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "helpers.h"
#include "Gui.h"
#include "Renderer.h"

#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Node.h"

double mouseX, mouseY = 0.0;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &mouseX, &mouseY);
    }
}


void RenderLoop(GLFWwindow* window, Renderer& renderer, OrthographicCamera& camera, Gui& gui, FrameBuffer& fb, Shader& shader, Texture& texture, std::vector<Sprite>& sprites, std::vector<float*> & transforms){
 
        renderer.Clear();
        /*rendering */
        
        
        /*todo fix? */
        texture.Bind(1);

        fb.Bind();
        for (auto &&sprite : sprites)
        {
        shader.Bind();
		shader.SetUniform<int>("u_Texture", 1);
        sprite.SetPostion(glm::vec3(mouseX,mouseY,1));
        // std::cout << "(" << sprite.GetPosition().x <<","<<sprite.GetPosition().y<<")" <<std::endl;
        shader.SetUniform<glm::mat4>("u_ViewMatrix", camera.GetViewMatrix());
        shader.SetUniform<glm::mat4>("u_ProjectionMatrix", camera.GetProjectionMatrix());
        shader.SetUniform<glm::mat4>("u_ModelMatrix", glm::translate(glm::mat4(1.0f) , sprite.GetPosition()));
        // shader.SetUniform<glm::mat4>("u_ModelViewProjection", camera.GetViewProjectionMatrix());
        renderer.Draw(sprite.GetVertexArray());
        }
        fb.Unbind();
        gui.Begin();
        gui.Update(fb, transforms);
        gui.End();
        
        glfwSwapBuffers(window);
        glfwPollEvents();


}
int main()
{	



    if(!glfwInit()){
        std::cout << "Failed to init glfw" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // opengl 4.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // opengl 4.6
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // tells glfw to use modern opengl

    
	GLFWwindow* window = glfwCreateWindow(800, 600, "phlawlessEngine", NULL, NULL);
	if (window == NULL)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
    }

	glfwMakeContextCurrent(window);

    if(glewInit()!= GLEW_OK){
        std::cout << "Failed to init glew " << std::endl;
    }
//    default blend settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    OrthographicCamera camera = OrthographicCamera(0.0f,10.0f,10.0f,0.0f);
	std::vector<Sprite> sprites {Sprite(), Sprite()};
    std::vector<float*> transforms;
    for (auto &&sprite : sprites)
    {
        transforms.push_back(sprite.GetTransform());
    }
    
    

    int sceneWidth = 640;
    int sceneHeight = 480;
    FrameBuffer fb = FrameBuffer(sceneWidth,sceneHeight);

    Gui gui = Gui(window);
    
	
    Shader shader("../shaders/Basic.shader");
    
    Texture texture("../res/textures/dice.png");

	Renderer renderer = Renderer();

	 while (!glfwWindowShouldClose(window))
    {	
    
		RenderLoop(window,renderer,camera,gui,fb,shader,texture,sprites, transforms);
	}
	ImGui_ImplGlfw_Shutdown();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 1;
}