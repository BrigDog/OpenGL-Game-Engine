#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
};