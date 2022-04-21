#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>


struct ShaderProgramSource{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath){
	std::ifstream stream(filePath);
	enum class ShaderType{
		NONE = -1, VERTEX =0 , FRAGMENT = 1
	};
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while(getline(stream,line)){
		if(line.find("#shader") != std::string::npos){
		if(line.find("vertex") != std::string::npos)
			type = ShaderType::VERTEX;
		else if(line.find("fragment") != std::string::npos)
			type = ShaderType::FRAGMENT;
		}
		else{
			ss[(int)type] << line << "\n";
		}
	}
	return {ss[0].str(),ss[1].str()};
}

static unsigned int CompileShader( unsigned int type, const std::string& source){

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id,GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE){

		int length;
		glGetShaderiv(id,GL_INFO_LOG_LENGTH, &length);

		char* message = (char*) alloca((length*sizeof(char)));
		glGetShaderInfoLog(id,length,&length,message);

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		return 0;
	}

	return id;

}


static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

	glAttachShader(program,vs);
	glAttachShader(program,fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main()
{
	GLFWwindow* window;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // tells glfw to use modern opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // opengl 4.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // opengl 4.6

	// Initialize GLFW
	if(!glfwInit()){
		return -1;
	}
	
	
	window = glfwCreateWindow(800, 600, "phlawlessEngine", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	//init glew
	if(glewInit()!= GLEW_OK){
		std::cout << "Failed to init GLEW " << std::endl;
	}
	const unsigned int positionsLength = 8;
	float positions[positionsLength]= {
		-0.1f, -0.1f,
		0.1f, -0.1f,
		0.1f, 0.1f,
     	-0.1f, 0.1f,
	};
	unsigned int indicies[]={
		0,1,2,
		2,3,0
	};
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//create a buffer bind it and add data
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);
	//need to enable the atrib array
	glEnableVertexAttribArray(0);
	// tell opengl the layout of our vertices
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),0);

	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_DYNAMIC_DRAW);
	
	ShaderProgramSource source = ParseShader("../shaders/Basic.shader");

	unsigned int shader = CreateShader(source.VertexSource,source.FragmentSource);
	glUseProgram(shader);
	int location = glGetUniformLocation(shader,"u_Color");
	float red= 0.0f;
	float increment = 2.0f;
	/* test movement code */
	// /* 
	double currentTime;
	double lastTime = glfwGetTime(); 
	float deltaTime;
	float speed = 3.0f;
	//  */
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{	
		/* test movement code */
		// /* 
		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;
		if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
			for(int i=0 ;i<positionsLength; i++){
				if(i%2!=0){
    			positions[i] += speed*deltaTime;
				}
			}
		}
		if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
    	for(int i=0 ;i<positionsLength; i++){
				if(i%2!=0){
    			positions[i] -= speed*deltaTime;
				}
			}
		}
		if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
    		for(int i=0 ;i<positionsLength; i++){
				if(i%2==0){
    			positions[i] += speed*deltaTime;
				}
			}
		}
		if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
    	for(int i=0 ;i<positionsLength; i++){
				if(i%2==0){
    			positions[i] -= speed*deltaTime;
				}
			}
		}
		// */
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		/* render here */
	
		glUniform4f(location, red, 0.3f, 0.8f, 1.0f);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
		red += increment * deltaTime;
		if(red> 1.0f || red<0.0f){
			increment*=-1.0f;
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}