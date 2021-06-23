#pragma once

#include <glad/glad.h>
#include "glutil.hpp"

class VBO {
public:
    VBO();
    ~VBO();

private:
    unsigned int id;
};