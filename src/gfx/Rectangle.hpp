#pragma once

#include "glutil.hpp"

#include "IEntity.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "ShaderProgram.hpp"

#include "Colors.hpp"

struct RectangleBounds {
    RectangleBounds(float width, float height);
    bool inBounds(glm::vec2 point);

    glm::vec2 topLeft;
    glm::vec2 topRight;
    glm::vec2 bottomLeft;
    glm::vec2 bottomRight;
};

class Rectangle : public IEntity {
public:
    Rectangle(float width, float height, glm::vec4 color);
    ~Rectangle();

    // TODO: change this to a vec2
    void translate(float x, float y);
    void changeColor(const glm::vec4 color);
    void draw() override;
    void toString();

    /**
     * Should be called once on application start to set static shader for all Rectanlge objects.
     */
    static void setShader(std::shared_ptr<ShaderProgram> sp);
    glm::vec2 getCurrentPos() { return currentPos; }
    glm::vec2 getCurrentPosCentre() { return glm::vec2(currentPos.x + this->width / 2, currentPos.y + this->height / 2); }
private:
    unsigned int id;
    glm::vec4 color;
    float width;
    float height;

    /**
     * currentPos always refers to the bottom left of the rectangle.
     */
    glm::vec2 currentPos;
    std::unique_ptr<RectangleBounds> bounds;

    std::unique_ptr<VAO> vao;
    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;
    static std::shared_ptr<ShaderProgram> sp;
};