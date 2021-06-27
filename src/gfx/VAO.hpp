#pragma once

#include "glutil.hpp"

class VAO {
public:
    VAO();
    ~VAO();

    void bind();
    void unbind();
    void configureVAOBuffer(unsigned int index, int size, GLenum type, int stride, unsigned int pointer);
private:
    unsigned int id;
};