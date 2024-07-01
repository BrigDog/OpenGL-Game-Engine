#include "../Header/Window.h"

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
    window = glfwCreateWindow(640, 480, "Disco Box", NULL, NULL);
    if (!window)
    {
        CHECKFUNCTION(glfwTerminate());
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        assert(false && "ERROR WITH GLEW IMPLEMENTATION");
    }

    std::cout << glGetString(GL_VERSION) << std::endl << std::endl << std::endl << std::endl;

    CHECKFUNCTION(glGenVertexArrays(1, &vao));
    CHECKFUNCTION(glBindVertexArray(vao));

    CHECKFUNCTION(glGenBuffers(1, &buffer));
    CHECKFUNCTION(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    CHECKFUNCTION(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW));

    CHECKFUNCTION(glEnableVertexAttribArray(0));
    CHECKFUNCTION(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    CHECKFUNCTION(glGenBuffers(1, &ibo));
    CHECKFUNCTION(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    CHECKFUNCTION(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW));

    ShaderProgramSource VertexShader = ParseShader("Resources/Shaders/BasicVertexShader.shader");
    std::cout << "Vertex Shader Code:" << std::endl << std::endl << VertexShader.ShaderCode << std::endl << std::endl << std::endl;
    ShaderProgramSource PixelShader = ParseShader("Resources/Shaders/BasicPixelShader.shader");
    std::cout << "Pixel Shader Code:" << std::endl << std::endl << PixelShader.ShaderCode << std::endl << std::endl;

    shader = CreateShader(VertexShader.ShaderCode, PixelShader.ShaderCode);
    CHECKFUNCTION(glUseProgram(shader));
 
    ShaderSetting.location = glGetUniformLocation(shader, "InputColor");
    CHECK(ShaderSetting.location != 1);
    CHECKFUNCTION(glUniform4f(ShaderSetting.location, ShaderSetting.inc, 0.3f, (ShaderSetting.inc * -1) + 1, 1.0f));

    CHECKFUNCTION(glBindVertexArray(0));
    CHECKFUNCTION(glUseProgram(0));
    CHECKFUNCTION(glBindBuffer(GL_ARRAY_BUFFER, 0));
    CHECKFUNCTION(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    return 0;
}

int Window::Update()
{


    ShaderSetting.inc += 0.001;
    if (ShaderSetting.inc > 1)
    {
        ShaderSetting.inc = 0;
    }



    /* Render here */
    CHECKFUNCTION(glClear(GL_COLOR_BUFFER_BIT));

    CHECKFUNCTION(glUseProgram(shader));
    CHECKFUNCTION(glUniform4f(ShaderSetting.location, ShaderSetting.inc, 0.3f, (ShaderSetting.inc * -1) + 1, 1.0f));

    CHECKFUNCTION(glBindVertexArray(vao));
    CHECKFUNCTION(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

    CHECKFUNCTION(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    /* Swap front and back buffers */
    CHECKFUNCTION(glfwSwapBuffers(window));

    /* Poll for and process events */
    CHECKFUNCTION(glfwPollEvents());

    return 0;
}

int Window::Terminate()
{
    CHECKFUNCTION(glDeleteProgram(shader));
    CHECKFUNCTION(glfwTerminate());
    
    return 0;
}