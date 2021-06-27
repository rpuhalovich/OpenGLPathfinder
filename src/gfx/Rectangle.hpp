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
    Rectangle(Colors color);
    ~Rectangle();

    void draw() override;
private:
    Colors color;
    float width;
    float height;

    unsigned int id;
    std::unique_ptr<VAO> vao;
    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;
    std::unique_ptr<ShaderProgram> sp;
};