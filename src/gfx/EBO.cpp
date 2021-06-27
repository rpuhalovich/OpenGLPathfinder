#include "EBO.hpp"

EBO::EBO(const int* indices, unsigned int size) {
    glc(glGenBuffers(1, &id));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * size, indices, GL_STATIC_DRAW);
}

EBO::~EBO() {

}

void EBO::bind()
{
}
