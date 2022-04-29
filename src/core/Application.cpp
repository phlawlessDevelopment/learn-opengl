
#include <memory>
#include <iostream>
#include "Application.h"

Application::Application()
    :m_Window(nullptr), m_Gui(m_Window,m_FrameBuffer), m_Renderer(),
    m_Width(800), m_Height(600),
    m_Shader(), m_VertexArray(nullptr),
    m_VertexBuffer(nullptr), m_IndexBuffer(nullptr),
    m_Camera(-2.0f,2.0f,-1.5f,1.5f)
{
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // tells glfw to use modern opengl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // opengl 4.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // opengl 4.6

    if(!glfwInit()){
        std::cout << "Failed to init glfw" << std::endl;
    }
    
	m_Window = glfwCreateWindow(m_Width, m_Height, "phlawlessEngine", NULL, NULL);
	if (m_Window == NULL)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
    }
	glfwMakeContextCurrent(m_Window);
    if(glewInit()!= GLEW_OK){
        std::cout << "Failed to init glew " << std::endl;
    }
//    default blend settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    
    std::shared_ptr<FrameBuffer> m_FrameBuffer;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::shared_ptr<VertexArray> m_VertexArray;
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    m_Camera = OrthographicCamera(-2.0f,2.0f,-1.5f,1.5f);
    
}


Application::~Application()
{       
        ImGui_ImplGlfw_Shutdown();
        glfwDestroyWindow(m_Window);
        glfwTerminate();
}
void Application::Run()
{
        /* temp stuf */
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


    VertexBufferLayout layout = VertexBufferLayout();

    layout.Push<float>(2);
    layout.Push<float>(2);
    layout.Push<float>(4);

    m_VertexBuffer.reset(VertexBuffer::Create(positions, positionsLength * sizeof(float)));
    m_IndexBuffer.reset(IndexBuffer::Create(indicies,indicesLength));
    m_VertexArray.reset(VertexArray::Create());
    m_SceneWidth = 640;
    m_SceneHeight = 480;
    m_FrameBuffer.reset(FrameBuffer::Create(m_SceneWidth,m_SceneHeight));
    m_Gui = Gui(m_Window,m_FrameBuffer);
    

    m_VertexBuffer -> SetLayout(layout);
    m_VertexArray -> AddVertexBuffer(m_VertexBuffer);
    m_VertexArray -> SetIndexBuffer(m_IndexBuffer);
    Shader m_Shader("../shaders/Basic.shader");
    Texture texture("../res/textures/dice.png");
    texture.Bind(0);
    m_Shader.Bind();
    // m_Shader.SetUniform<int>("u_Texture", 0);
    // m_Shader.SetUniform<glm::mat4>("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
    
    while (!glfwWindowShouldClose(m_Window))
    {	
    
        m_Renderer.Clear();
        /*rendering */
        m_FrameBuffer->Bind();
        m_Renderer.BeginScene();
        m_Renderer.Submit(m_VertexArray);
        m_Renderer.EndScene();
        m_FrameBuffer->Unbind();
        m_Gui.Begin();
        m_Gui.Update();
        m_Gui.End();
        
        glfwSwapBuffers(m_Window);
        glfwPollEvents();

    }
}
void Application::ResizeWindow(){
        // glfwGetWindowSize(m_Window, &m_Width, &m_Height);
        // glfwSetWindowAspectRatio(m_Window,4,3);
        // m_Shader.Bind();
        // glm::mat4 projection = glm::ortho(-2.0f,2.0f,150.0f,150.0f,-1.0f,1.0f);
        // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0));
        // glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0));
        // glm::mat4 mvp = projection * view * model;
        // m_Shader.SetUniform<glm::mat4>("u_ModelViewProjection",mvp);
        
}
