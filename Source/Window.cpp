#include "../Header/Window.h"
#include <cstddef>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define CHECK(x) if(!(x)) __debugbreak();
#define CHECKFUNCTION(x) GLClearError();\
    x;\
    CHECK(GLLogCall(#x, __FILE__, __LINE__));

enum ShaderType
{
    NONE = 0, VERTEX = 0, PIXEL = 1,
};

struct ShaderProgramSource
{
    std::string ShaderCode;
    ShaderType Type;
};

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ") FROM " << function << " ON LINE " << line << " WITHIN " << file << std::endl;
        return false;
    }
    return true;
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
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

static unsigned int CreateShader(const std::string& vertexShader, const std::string& pixelShader)
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
    CHECKFUNCTION(glGenBuffers(1, &buffer));
    CHECKFUNCTION(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    CHECKFUNCTION(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW));

    CHECKFUNCTION(glEnableVertexAttribArray(0));
    CHECKFUNCTION(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    unsigned int ibo;
    CHECKFUNCTION(glGenBuffers(1, &ibo));
    CHECKFUNCTION(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    CHECKFUNCTION(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW));

    ShaderProgramSource VertexShader = ParseShader("Resources/Shaders/BasicVertexShader.shader");
    std::cout << "Vertex Shader Code:" << std::endl << std::endl << VertexShader.ShaderCode << std::endl << std::endl << std::endl << std::endl << std::endl;
    ShaderProgramSource PixelShader = ParseShader("Resources/Shaders/BasicPixelShader.shader");
    std::cout << "Pixel Shader Code:" << std::endl << std::endl << PixelShader.ShaderCode << std::endl << std::endl;

    shader = CreateShader(VertexShader.ShaderCode, PixelShader.ShaderCode);
    glUseProgram(shader);
    return 0;
}

int Window::Update()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    CHECKFUNCTION(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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