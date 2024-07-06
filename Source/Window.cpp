#include "../Header/Window.h"

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

    va.SettupVertexArray();

    vb.Settup(positions, 8 * sizeof(float));

    layout.Push<float>(2);

    va.AddBuffer(vb, layout);

    ib.Settup(indicies, 6);

    m_Shader.SettupShader("Resources/Shaders/BasicVertexShader.shader", "Resources/Shaders/BasicPixelShader.shader");
    m_Shader.Bind();

    m_Shader.SetUniform4f("InputColor", ShaderSetting.inc, 0.3f, (ShaderSetting.inc * -1) + 1, 1.0f);

    va.Unbind();
    m_Shader.Unbind();
    vb.Unbind();
    ib.Unbind();

    return 0;
}

int Window::Update()
{


    ShaderSetting.inc += 0.001f;
    if (ShaderSetting.inc > 1)
    {
        ShaderSetting.inc = 0;
    }



    /* Render here */
    CHECKFUNCTION(glClear(GL_COLOR_BUFFER_BIT));

    m_Shader.Bind();
    m_Shader.SetUniform4f("InputColor", ShaderSetting.inc, 0.3f, (ShaderSetting.inc * -1) + 1, 1.0f);

    va.Bind();
    ib.Bind();

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
