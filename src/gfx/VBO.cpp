#include "vbo.hpp"

VBO::VBO(const float* verts, unsigned int size) {
    glc(glGenBuffers(1, &id));

    bind();
    glc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, verts, GL_STATIC_DRAW));
}

VBO::~VBO() {
    glc(glDeleteBuffers(1, &id));
}

void VBO::bind() {
    glc(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VBO::unbind()
{
}
