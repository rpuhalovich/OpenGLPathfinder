#pragma once

#include "glutil.hpp"

class EBO {
public:
    EBO(const int* indicies, unsigned int size);
    ~EBO();

    void bind();
private:
    unsigned int id;
};