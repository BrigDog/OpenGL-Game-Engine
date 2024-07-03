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

void GLClearError();
void GLCheckError();
bool GLLogCall(const char* function, const char* file, int line);

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

class VertexBuffer
{
public:
	~VertexBuffer();
	void Settup(const void* data, unsigned int count);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int RenderID;
};

class IndexBuffer
{
public:
	~IndexBuffer();
	void Settup(const unsigned int* data, unsigned int count);
	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return M_Count; }
private:
	unsigned int RenderID;
	unsigned int M_Count;
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
	unsigned int vao;
	unsigned int ibo;
	unsigned int buffer;
	unsigned int shader;
	ShaderSettings ShaderSetting;


	VertexBuffer vb;
	IndexBuffer ib;
};