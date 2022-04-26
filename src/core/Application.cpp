#include "Application.h"

Application::Application()
    :m_Width(0), m_Height(0)
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // tells glfw to use modern opengl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // opengl 4.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // opengl 4.6

    if(!glfwInit()){
        std::cout << "Failed to init glfw" << std::endl;
    }
    
    m_Window = glfwCreateWindow(640, 480, "phlawlessEngine", NULL, NULL);
    if (m_Window == NULL)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_Window);
    if(glewInit()!= GLEW_OK){
        std::cout << "Failed to init glew " << std::endl;
    }
    // default blend settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    m_Renderer = Renderer();
    m_Gui = Gui(m_Window);

    /* temp stuff */

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

RenderSet rs = {va,vb,layout,ib,shader};
m_Renderer.AddRenderSet(rs);
}
Application::~Application()
{
        glfwDestroyWindow(m_Window);
        glfwTerminate();
}
void Application::Run()
{
    while (!glfwWindowShouldClose(m_Window))
{	
    m_Renderer.Clear();
    /*rendering */
    m_Renderer.Draw();
    m_Gui.Render();	
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
    
    // shader.Bind();
    // {
    // 	glm::mat4 model = glm::translate(glm::mat4(1.0f),translationA);
    // 	glm::mat4 mvp = projection * view * model;
    // 	shader.SetUniform<glm::mat4>("u_ModelViewProjection",mvp);
    // }
    // {
    // 	glm::mat4 model = glm::translate(glm::mat4(1.0f),translationB);
    // 	glm::mat4 mvp = projection * view * model;
    // 	shader.SetUniform<glm::mat4>("u_ModelViewProjection",mvp);
    // 	renderer.Draw(va,ib,shader);
    // }
    

    /*end rendering */

}
}
