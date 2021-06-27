#include "Square.hpp"

Square::Square(Colors color) :
    color(color)
{

}

Square::~Square() {
}

void Square::draw() {
    sp->use();

    vao->bind();
    glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    vao->unbind();

    //glc(glBindVertexArray(vao->));
    //glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    //glc(glBindVertexArray(0));
}
