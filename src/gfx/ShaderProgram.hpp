#pragma once

#include <glad/glad.h>
#include "glutil.hpp"
#include "Shader.hpp"

class ShaderProgram {
public:
    ShaderProgram(const char* vertname, const char* fragname);
    ~ShaderProgram();

    void use();

    unsigned int getId() { return id; }
private:
    unsigned int id;
};