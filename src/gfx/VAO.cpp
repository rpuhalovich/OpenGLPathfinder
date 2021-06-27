#include "VAO.hpp"

VAO::VAO() {
    glc(glGenVertexArrays(1, &id));
}

VAO::~VAO() {
    glc(glDeleteVertexArrays(1, &id));
}

void VAO::bind() {
    glc(glBindVertexArray(id));
}

void VAO::unbind() {
    glc(glBindVertexArray(0));
}

void VAO::configureVAOBuffer(unsigned int index, int size, GLenum type, int stride, unsigned int pointer) {
    switch (type) {
        case GL_FLOAT: {
            glc(glVertexAttribPointer(index, size, type, GL_FALSE, stride * sizeof(float), (void*)(pointer * sizeof(float))));
            break;
        }
        case GL_INT: {
            glc(glVertexAttribPointer(index, size, type, GL_FALSE, stride * sizeof(int), (void*)(pointer * sizeof(int))));
            break;
        }
    }
    glc(glEnableVertexAttribArray(0));
    glc(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
