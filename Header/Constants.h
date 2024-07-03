#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ") FROM " << function << " ON LINE " << line << " WITHIN " << file << std::endl;
        return false;
    }
    return true;
}

#define CHECK(x) if(!(x)) __debugbreak();

#define CHECKFUNCTION(x)	GLClearError();\
							x;\
							CHECK(GLLogCall(#x, __FILE__, __LINE__));