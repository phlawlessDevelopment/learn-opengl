#pragma once

#include <GL/glew.h>
#include <assert.h>

#define GLCall(x) GLClearError();\
    x;\
    assert(GLLogCall(#x,__FILE__,__LINE__))


void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);