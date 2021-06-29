#include "Rectangle.hpp"

Rectangle::Rectangle(float width, float height, glm::vec4 color, std::shared_ptr<ShaderProgram> sp) :
    sp(sp)
{
    float vertices[] = {
         1.0f, 1.0f, 0.0f, color.x, color.y, color.z, // top right
         1.0f, 0.0f, 0.0f, color.x, color.y, color.z, // bottom right
         0.0f, 0.0f, 0.0f, color.x, color.y, color.z, // bottom left
         0.0f, 1.0f, 0.0f, color.x, color.y, color.z  // top left
    };

    int indices[] = {
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };

    vao = std::make_unique<VAO>();
    vao->bind();

    vbo = std::make_unique<VBO>(vertices, sizeof(vertices));
    ebo = std::make_unique<EBO>(indices, sizeof(indices));

    vao->configureVAOBuffer(0, 3, GL_FLOAT, 6, 0); // positions
    vao->configureVAOBuffer(1, 3, GL_FLOAT, 6, 3); // color

    vbo->unbind();
    vao->unbind();
}

Rectangle::~Rectangle() {

}

void Rectangle::draw() {
    sp->use();
    vao->bind();
    glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    vao->unbind();
}
