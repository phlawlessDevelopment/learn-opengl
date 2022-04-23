#include <iostream>
#include <GL/glew.h>
#include "GLErrors.h"

void GLClearError()
{
    while(glGetError());
}
bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL error] (" << error <<") " << function << " " << file << ":" <<line<< std::endl;
        return false;
    }
    return true;
}
