#pragma once

#include "glutil.hpp"

#include "IEntity.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "ShaderProgram.hpp"

#include "Colors.hpp"

class Rectangle : public IEntity {
public:
    Rectangle(float width, float height, glm::vec4 color, std::shared_ptr<ShaderProgram> sp);
    ~Rectangle();

    void translate(float x, float y);

    void draw() override;
private:
    glm::vec4 color;
    float width;
    float height;

    unsigned int id;
    std::unique_ptr<VAO> vao;
    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;
    std::shared_ptr<ShaderProgram> sp;
};