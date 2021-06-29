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
    Rectangle(float width, float height, glm::vec4 color);
    ~Rectangle();

    void translate(float x, float y);
    void draw() override;

    static void setShader(std::shared_ptr<ShaderProgram> sp);
private:
    unsigned int id;
    glm::vec4 color;
    float width;
    float height;

    std::unique_ptr<VAO> vao;
    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;
    static std::shared_ptr<ShaderProgram> sp;
};