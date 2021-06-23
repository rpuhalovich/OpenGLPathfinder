#include "vbo.hpp"

VBO::VBO() {
    glc(glGenBuffers(1, &id));
}

VBO::~VBO() {
    glc(glDeleteBuffers(1, &id));
}
