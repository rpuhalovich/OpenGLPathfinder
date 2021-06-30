#include "Rectangle.hpp"

// see: https://stackoverflow.com/questions/16049306/error-lnk2001-unresolved-external-symbol-private-static-class
std::shared_ptr<ShaderProgram> Rectangle::sp;

Rectangle::Rectangle(float width, float height, glm::vec4 color, RectangleType type) :
    width(width), height(height)
{
    float vertices[] = {
         width, height, 0.0f, color.x, color.y, color.z, // top right
         width, 0.0f,   0.0f, color.x, color.y, color.z, // bottom right
         0.0f,  0.0f,   0.0f, color.x, color.y, color.z, // bottom left
         0.0f,  height, 0.0f, color.x, color.y, color.z  // top left
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

    currentPos = glm::vec2(0.0f, 0.0f);

    bounds = std::make_unique<RectangleBounds>(width, height);

    this->color = color;
}

Rectangle::~Rectangle() {

}

// TODO: Make check such that we don't change every draw call.
void Rectangle::translate(float x, float y) {
    // update position
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
    currentPos = glm::vec2(x, y);

    // update bounds
    bounds->bottomLeft = glm::vec2(x, y);
    bounds->bottomRight = glm::vec2(x + width, y);
    bounds->topLeft = glm::vec2(x, y + height);
    bounds->topRight = glm::vec2(x + width, y + height);

    sp->setMat4Uniform4fv(trans, std::string("model"));
}

// TODO: Make check such that we don't change every draw call.
void Rectangle::changeColor(const glm::vec4 color) {
    this->color = color;
    sp->setMat4Uniform4iv(color, "changeColor");
}

void Rectangle::draw() {
    translate(currentPos.x, currentPos.y);
    changeColor(color);

    sp->use();
    vao->bind();
    glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    vao->unbind();
}

void Rectangle::toString() {
    std::cout << "Rectangle at: (" << this->currentPos.x << "x, " << this->currentPos.y << "y)." << std::endl;
}

void Rectangle::OnUpdate(glm::vec2 location, int button, int action) {
    if (button == GLFW_KEY_Y && action == GLFW_PRESS) {
        changeColor(Colors::LIGHT_RED);
    } else if (bounds->inBounds(location) && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "location.x: " << location.x << " location.y: " << location.y << std::endl;
        changeColor(Colors::LIGHT_RED);
    }
}

void Rectangle::setShader(std::shared_ptr<ShaderProgram> _sp) {
    Rectangle::sp = _sp;
}

RectangleBounds::RectangleBounds(float width, float height) {
    topLeft = glm::vec2(0.0f, height);
    topRight = glm::vec2(width, height);
    bottomLeft = glm::vec2(0.0f, 0.0f);
    bottomRight = glm::vec2(width, 0.0f);
}

bool RectangleBounds::inBounds(glm::vec2 point) {
    return point.x >= this->bottomLeft.x && point.x <= this->bottomRight.x && point.y <= this->topRight.y && point.y >= this->bottomLeft.y;
}
