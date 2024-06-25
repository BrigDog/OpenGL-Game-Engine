#pragma once
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