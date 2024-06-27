#include "../Header/Window.h"
#include <cstddef>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

enum ShaderType
{
    NONE = -1, VERTEX = 0, PIXEL = 1,
};

struct ShaderProgramSource
{
    std::string ShaderCode;
    ShaderType Type;
};

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "pixel")
            << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& pixelShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int ps = CompileShader(GL_FRAGMENT_SHADER, pixelShader);

    glAttachShader(program, vs);
    glAttachShader(program, ps);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(ps);

    return program;
}

static ShaderProgramSource ParseShader(const std::string& FilePath)
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
                assert(false, "ERROR IDENTIFYING SHADER RESOURCE");
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

int Window::Init()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        assert(false && "ERROR WITH GLEW IMPLEMENTATION");
    }

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    ShaderProgramSource VertexShader = ParseShader("Resources/Shaders/BasicVertexShader.shader");
    ShaderProgramSource PixelShader = ParseShader("Resources/Shaders/BasicPixelShader.shader");

    shader = CreateShader(VertexShader.ShaderCode, PixelShader.ShaderCode);
    glUseProgram(shader);
    return 0;
}

int Window::Update()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);


    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    return 0;
}

int Window::Terminate()
{
    glDeleteProgram(shader);
    glfwTerminate();
    
    return 0;
}