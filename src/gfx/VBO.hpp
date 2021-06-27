#pragma once

#include <glad/glad.h>
#include "glutil.hpp"

class VBO {
public:
    VBO(const float* verts, unsigned int size);
    ~VBO();

    void bind();
    void unbind();
private:
    unsigned int id;
};
