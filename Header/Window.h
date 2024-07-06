#pragma once

#include <cstddef>
#include <cassert>
#include <fstream>
#include <sstream>

#include "Constants.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

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
	unsigned int vao;
	unsigned int ibo;
	unsigned int buffer;
	unsigned int shader;
	ShaderSettings ShaderSetting;

	VertexBuffer vb;
	IndexBuffer ib;
	VertexArray va;
	VertexBuffer vba;
	VertexBufferLayout layout;
	Shader m_Shader;
};
