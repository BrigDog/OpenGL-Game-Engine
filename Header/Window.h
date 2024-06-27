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
	float positions[6] = {
		-0.5f, -0.2f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};
	unsigned int shader;
};