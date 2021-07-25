#pragma once

#include "leakdetector.hpp"
#include "util.hpp"

// --- gfx ---
#include "Window.hpp"
#include "Rectangle.hpp"
#include "Colors.hpp"

struct RendererHints {
    float winWidth = 1280.0f;
    float winHeight = 720.0f;
    std::string winTitle = std::string("Hello World");
    bool maximised = true;
    bool resizable = true;
};

class Renderer {
public:
    static std::unique_ptr<Window> init(RendererHints* rh) {
        initRand();

        // Note: Window should exist before setting shaders as a context is needed.
        std::unique_ptr<Window> window = std::make_unique<Window>(rh->winWidth, rh->winHeight, rh->winTitle, rh->maximised, rh->resizable);

        // Set shaders of any entities.
        Rectangle::setShader("Rectangle.vert", "Rectangle.frag", rh->winWidth, rh->winHeight);

        return window;
    }
};
