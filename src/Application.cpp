#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = new Window(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
}

Application::~Application() {
    delete window;
}

void Application::run() {
    std::unique_ptr<ShaderProgram> sp = std::make_unique<ShaderProgram>("vs.vert", "fs.frag");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // --- copied -------------------------------------------------------------
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string temp = Shader::readShader("vs.vert").c_str();
    const char* vs = temp.c_str();
    glShaderSource(vertexShader, 1, &vs, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    temp = Shader::readShader("fs.frag").c_str();
    const char* fs = temp.c_str();
    glShaderSource(fragmentShader, 1, &fs, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // ------------------------------------------------------------------------

    // Generate buffers (VAO, VBO)
    unsigned int VBO, VAO;
    glc(glGenVertexArrays(1, &VAO)); 
    glc(glGenBuffers(1, &VBO));

    glc(glBindVertexArray(VAO));

    // Configure the VBO
    glc(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    glc(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    glc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    glc(glEnableVertexAttribArray(0));
    glc(glBindBuffer(GL_ARRAY_BUFFER, 0));

    // Unbind the VAO
    glc(glBindVertexArray(0));

    // Run loop.
    while (!window->shouldWindowClose()) {
        window->beginFrame();

        // bg colour
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        // triangle
        //sp->use();
        //glc(glUseProgram(sp->getId()));
        glc(glUseProgram(shaderProgram));

        glc(glBindVertexArray(VAO));
        glc(glDrawArrays(GL_TRIANGLES, 0, 3));
        //glc(glBindVertexArray(0));

        window->endFrame();
    }

    glc(glDeleteVertexArrays(1, &VAO));
    glc(glDeleteBuffers(1, &VBO));
}
