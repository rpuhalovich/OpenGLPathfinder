#pragma once

#include <glad/glad.h>
#include "glutil.hpp"
#include "Shader.hpp"

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertname, const std::string& fragname);
    ~ShaderProgram();

    void use();

    unsigned int getId() { return id; }
private:
    unsigned int id;
};
