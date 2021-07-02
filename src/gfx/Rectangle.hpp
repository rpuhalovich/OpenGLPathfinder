#pragma once

#include "glutil.hpp"

#include "IEntity.hpp"
#include "IEventObserver.hpp"

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "ShaderProgram.hpp"

#include "Colors.hpp"

struct RectangleBounds {
    RectangleBounds(float width, float height);

    /**
     * \return True if the point is inside the bounds of this object.
     */
    bool inBounds(glm::vec2 point);

    glm::vec2 topLeft;
    glm::vec2 topRight;
    glm::vec2 bottomLeft;
    glm::vec2 bottomRight;
};

class Rectangle : public IEntity, public IEventObserver {
public:
    Rectangle(float width, float height, glm::vec4 color);
    ~Rectangle();

    void translate(glm::vec2 location);
    void changeColor(const glm::vec4 color);
    void draw() override;
    void toString();

    void onUpdate(glm::vec2 location, int button, int action) override;

    /**
     * Should be called once on application start to set static shader for all Rectanlge objects.
     */
    static void setShaderDimensions(int winWidth, int winHeight);
    glm::vec2 getCurrentPos() { return currentPos; }
    glm::vec2 getCurrentPosCentre() { return glm::vec2(currentPos.x + this->width / 2, currentPos.y + this->height / 2); }
    std::unique_ptr<RectangleBounds>& getBounds() { return bounds; }
protected:
    glm::vec4 currentColor;
    float width;
    float height;

    /**
     * currentPos always refers to the bottom left of the rectangle.
     */
    glm::vec2 currentPos;
    std::unique_ptr<RectangleBounds> bounds;
private:
    std::unique_ptr<VAO> vao;
    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;
    static std::shared_ptr<ShaderProgram> sp;
};
