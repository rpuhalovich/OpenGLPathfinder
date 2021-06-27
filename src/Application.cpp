#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = new Window(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
}

Application::~Application() {
    delete window;
}

void Application::run() {
    float vertices[] = {
         1.0f,  1.0f, 0.0f,  // top right
         1.0f,  0.0f, 0.0f,  // bottom right
         0.0f,  0.0f, 0.0f,  // bottom left
         0.0f,  1.0f, 0.0f   // top left
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    std::unique_ptr<Rectangle> r = std::make_unique<Rectangle>();

    //std::unique_ptr<ShaderProgram> sp = std::make_unique<ShaderProgram>(std::string("vs.vert"), std::string("fs.frag"));

    //// Generate buffers (VAO, VBO)
    //unsigned int VBO, VAO, EBO;
    //glc(glGenVertexArrays(1, &VAO));
    //glc(glGenBuffers(1, &VBO));
    //glc(glGenBuffers(1, &EBO));

    //// Bind the VAO
    //glc(glBindVertexArray(VAO));

    //// Configure the VBO and EBO
    //glc(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    //glc(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //glc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    //glc(glEnableVertexAttribArray(0));

    //glc(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Note: don't unbind EBO. VBO is fine.

    //// Unbind the VAO
    //glc(glBindVertexArray(0));

    // Run loop.
    while (!window->shouldWindowClose()) {
        window->beginFrame();

        // bg colour
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        //sp->use();

        //glc(glBindVertexArray(VAO));
        //glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        //glc(glBindVertexArray(0));

        window->endFrame();
    }

    glc(glDeleteVertexArrays(1, &VAO));
    glc(glDeleteBuffers(1, &VBO));
}
