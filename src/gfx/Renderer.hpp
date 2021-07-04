#pragma once

#include "leakdetector.hpp"

// --- gfx ---
#include "Window.hpp"
#include "Rectangle.hpp"
#include "Colors.hpp"

class Renderer {
public:
    void init(float winWidth, float winHeight) {
        Rectangle::setShaderDimensions(winWidth, winHeight);
    }
};