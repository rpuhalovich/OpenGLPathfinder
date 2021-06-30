#pragma once

#include "glutil.hpp"

class EBO {
public:
    EBO(const int* indices, size_t size);
    ~EBO();

    void bind();
private:
    unsigned int id;
};
