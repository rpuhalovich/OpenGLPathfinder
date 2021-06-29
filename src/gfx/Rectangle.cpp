#include "Rectangle.hpp"

Rectangle::Rectangle(float width, float height, glm::vec4 color, std::shared_ptr<ShaderProgram> sp) :
    sp(sp)
{
    float vertices[] = {
         width, height, 0.0f, color.x, color.y, color.z, // top right
         width, 0.0f, 0.0f, color.x, color.y, color.z, // bottom right
         0.0f, 0.0f, 0.0f, color.x, color.y, color.z, // bottom left
         0.0f, height, 0.0f, color.x, color.y, color.z  // top left
    };

    int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
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

void Rectangle::translate(float x, float y) {
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
    sp->setMat4(trans, std::string("model"));
}

void Rectangle::draw() {
    sp->use();
    vao->bind();
    glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    vao->unbind();
}
