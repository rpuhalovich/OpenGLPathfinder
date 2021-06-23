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

    // Generate buffers (VAO, VBO, EBO)
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

        sp->use();

        glc(glBindVertexArray(VAO));
        glc(glDrawArrays(GL_TRIANGLES, 0, 3));
        glc(glBindVertexArray(0));

        window->endFrame();
    }
}
