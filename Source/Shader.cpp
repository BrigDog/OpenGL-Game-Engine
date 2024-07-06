#include "../Header/Shader.h"

void Shader::SettupShader(const std::string& VertexShaderFilePath, const std::string& PixelShaderFilePath)
{
	m_VertexFilePath = VertexShaderFilePath;
	m_PixelFilePath = PixelShaderFilePath;

	m_Renderer_ID = 0;

	ShaderProgramSource VertexShader = ParseShader(m_VertexFilePath);
	std::cout << "Vertex Shader Code:" << std::endl << std::endl << VertexShader.ShaderCode << std::endl << std::endl << std::endl;
	ShaderProgramSource PixelShader = ParseShader(m_PixelFilePath);
	std::cout << "Pixel Shader Code:" << std::endl << std::endl << PixelShader.ShaderCode << std::endl << std::endl;

	m_Renderer_ID = CreateShader(VertexShader.ShaderCode, PixelShader.ShaderCode);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	CHECKFUNCTION(glShaderSource(id, 1, &src, nullptr));
	CHECKFUNCTION(glCompileShader(id));

	int result;
	CHECKFUNCTION(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		CHECKFUNCTION(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		CHECKFUNCTION(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "pixel")
			<< " shader!" << std::endl;
		std::cout << message << std::endl;
		CHECKFUNCTION(glDeleteShader(id));
		return 0;
	}

	return id;
}

void Shader::Bind() const
{
	CHECKFUNCTION(glUseProgram(m_Renderer_ID));
}

void Shader::Unbind() const
{
	CHECKFUNCTION(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	CHECKFUNCTION(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3))
}

ShaderProgramSource Shader::ParseShader(const std::string& FilePath)
{
	std::ifstream stream(FilePath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = NONE;

	while (getline(stream, line))
	{
		if (line.find("#Shader") != std::string::npos)
		{
			if (line.find("Vertex") != std::string::npos)
			{
				type = VERTEX;
			}
			else if (line.find("Pixel") != std::string::npos)
			{
				type = PIXEL;
			}
			else
			{
				type = NONE;
				//assert(false, "ERROR IDENTIFYING SHADER RESOURCE");
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	ShaderProgramSource Result;
	Result.ShaderCode = ss[(int)type].str();
	Result.Type = type;
	return Result;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& pixelShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int ps = CompileShader(GL_FRAGMENT_SHADER, pixelShader);

	CHECKFUNCTION(glAttachShader(program, vs));
	CHECKFUNCTION(glAttachShader(program, ps));

	CHECKFUNCTION(glLinkProgram(program));
	CHECKFUNCTION(glValidateProgram(program));

	CHECKFUNCTION(glDeleteShader(vs));
	CHECKFUNCTION(glDeleteShader(ps));

	return program;
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	unsigned int location = 0;
	CHECKFUNCTION(location = glGetUniformLocation(m_Renderer_ID, name.c_str()));

	m_UniformLocationCache[name] = location;
	return location;
}
