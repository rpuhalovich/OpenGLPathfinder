#pragma once

#include <GLFW/glfw3.h>

/**
 * Abstract class that describes everything an entity needs to have.
 */
class Entity {
public:
    virtual void draw() = 0;
};