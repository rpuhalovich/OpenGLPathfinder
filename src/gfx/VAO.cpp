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

void VAO::configureVAOBuffer(int index, int size, GLenum type, int stride, int pointer) {
    glc(glEnableVertexAttribArray(index));
    switch (type) {
        case GL_FLOAT: {
            glc(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(pointer * sizeof(float))));
            break;
        }
        case GL_INT: {
            glc(glVertexAttribPointer(index, size, GL_INT, GL_FALSE, stride * sizeof(int), (void*)(pointer * sizeof(int))));
            break;
        }
    }
}
