#pragma once

#include "Constants.h"
#include <unordered_map>

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

class Shader
{
public:
	void SettupShader(const std::string& VertexShaderFilePath, const std::string& PixelShaderFilePath);

	unsigned int CompileShader(unsigned int type, const std::string& source);
	
	void Bind() const;
	void Unbind() const;

	// Set Uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	ShaderProgramSource ParseShader(const std::string& FilePath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& pixelShader);
	unsigned int GetUniformLocation(const std::string& name);

	std::string m_VertexFilePath;
	std::string m_PixelFilePath;
	unsigned int m_Renderer_ID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
};
