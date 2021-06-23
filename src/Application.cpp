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

//    unsigned int vbo;
//    glc(glGenBuffers(1, &vbo));
//    glc(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//    glc(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//    glc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
//    glc(glEnableVertexAttribArray(0));

    sp->use();

    // Run loop.
    while (!window->shouldWindowClose()) {
        window->beginFrame();

        window->endFrame();
    }
}
