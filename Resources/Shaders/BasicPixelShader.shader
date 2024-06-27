#Shader Pixel
#version 330 core
layout(location = 0) out vec4 color;
uniform vec4 InputColor;
void main()
{
	color = InputColor;
};