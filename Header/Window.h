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
};