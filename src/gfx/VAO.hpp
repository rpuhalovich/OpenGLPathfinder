#pragma once

#include "glutil.hpp"

class VAO {
public:
    VAO();
    ~VAO();

    void bind();
    void unbind();
    void configureVAOBuffer(int index, int size, GLenum type, int stride, int pointer);
private:
    unsigned int id;
};