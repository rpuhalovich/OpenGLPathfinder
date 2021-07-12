#include "Rectangle.hpp"

// see: https://stackoverflow.com/questions/16049306/error-lnk2001-unresolved-external-symbol-private-static-class
std::shared_ptr<ShaderProgram> Rectangle::sp;

Rectangle::Rectangle(float width, float height, glm::vec4 color) :
    width(width), height(height), currentColor(color), 
    bounds(std::make_unique<RectangleBounds>(width, height)),
    currentPos(glm::vec2(0.0f, 0.0f))
{
    float vertices[] = {
         width, height, 0.0f, // top right
         width, 0.0f,   0.0f, // bottom right
         0.0f,  0.0f,   0.0f, // bottom left
         0.0f,  height, 0.0f  // top left
    };

    int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    vao = std::make_unique<VAO>();
    vao->bind();

    vbo = std::make_unique<VBO>(vertices, sizeof(vertices));
    ebo = std::make_unique<EBO>(indices, sizeof(indices));

    vao->configureVAOBuffer(0, 3, GL_FLOAT, 3, 0); // positions

    vbo->unbind();
    vao->unbind();
}

Rectangle::~Rectangle() {

}

void Rectangle::translate(glm::vec2 location) {
    // update position
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(location.x, location.y, 0.0f));
    currentPos = glm::vec2(location.x, location.y);

    // update bounds
    bounds->bottomLeft = glm::vec2(location.x, location.y);
    bounds->bottomRight = glm::vec2(location.x + width, location.y);
    bounds->topLeft = glm::vec2(location.x, location.y + height);
    bounds->topRight = glm::vec2(location.x + width, location.y + height);

    sp->setMat4Uniform4fv(trans, std::string("model"));
}

void Rectangle::changeColor(const glm::vec4 color) {
    this->currentColor = color;
    sp->setMat4Uniform4iv(currentColor, "changeColor");
}

void Rectangle::draw() {
    translate(currentPos);
    changeColor(currentColor);

    sp->use();
    vao->bind();
    glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    vao->unbind();
}

void Rectangle::toString() {
    std::cout << "Rectangle at: (" << currentPos.x << "x, " << currentPos.y << "y)" << std::endl;
}

void Rectangle::onUpdate(glm::vec2 location, int button, int action) {

}

void Rectangle::setShader(const std::string& vertname, const std::string& fragname, float winWidth, float winHeight) {
    Rectangle::sp = std::make_shared<ShaderProgram>(vertname.c_str(), fragname.c_str(), winWidth, winHeight);
}

RectangleBounds::RectangleBounds(float width, float height) {
    topLeft = glm::vec2(0.0f, height);
    topRight = glm::vec2(width, height);
    bottomLeft = glm::vec2(0.0f, 0.0f);
    bottomRight = glm::vec2(width, 0.0f);
}

bool RectangleBounds::inBounds(glm::vec2 point) {
    return point.x >= this->bottomLeft.x &&
           point.x <= this->bottomRight.x &&
           point.y <= this->topRight.y &&
           point.y >= this->bottomLeft.y;
}
