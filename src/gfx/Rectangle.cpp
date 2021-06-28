#include "Rectangle.hpp"

Rectangle::Rectangle() {
    sp = std::make_unique<ShaderProgram>("Rectangle.vert", "Rectangle.frag");

    float vertices[] = {
         1.0f,  1.0f, 0.0f, // top right
         1.0f,  0.0f, 0.0f, // bottom right
         0.0f,  0.0f, 0.0f, // bottom left
         0.0f,  1.0f, 0.0f  // top left
    };

    int indices[] = {
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };

    vao = std::make_unique<VAO>();
    vbo = std::make_unique<VBO>(vertices, sizeof(vertices));
    ebo = std::make_unique<EBO>(indices, sizeof(indices));
    vao->configureVAOBuffer(0, 3, GL_FLOAT, 3, 0);
}

Rectangle::~Rectangle() {

}

void Rectangle::draw() {
    sp->use();
    vao->bind();
    glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    vao->unbind();
}
