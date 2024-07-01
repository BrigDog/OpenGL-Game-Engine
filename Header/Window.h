#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Constants.h"
#include <string>
#include <cstddef>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

#define CHECKFUNCTION(x)	GLClearError();\
							x;\
							CHECK(GLLogCall(#x, __FILE__, __LINE__));

enum ShaderType
{
	NONE = -1, VERTEX = 0, PIXEL = 1,
};

struct ShaderProgramSource
{
	std::string ShaderCode;
	ShaderType Type;
};

struct ShaderSettings
{
	int location;
	float inc = 0;
};

class Window
{
public:
	int Init();
	int Update();
	int Terminate();
private:
	GLFWwindow* window;
	float positions[8] = {
		-0.5f, 0.0f,
		0.0f, 0.0f,
		0.0f, -0.5f,
		-0.5f, -0.5f
	};
	unsigned int indicies[6] = {
		0, 1, 2, 
		2, 3, 0
	};
	unsigned int shader;
	ShaderSettings ShaderSetting;
};