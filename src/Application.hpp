#pragma once

#include "Renderer.hpp"
#include "Board.hpp"
#include "GridPiece.hpp"

struct ApplicationHints {
    float winWidth;
    float winHeight;
    std::string winTitle;
    bool maximised;
    bool resizable;

    ApplicationHints() {
        winWidth = 1280.0f;
        winHeight = 720.0f;
        winTitle = std::string("Hello World");
        maximised = true;
        resizable = true;
    }
};

class Application {
public:
    Application(ApplicationHints* ah);
    ~Application();

    void run();
private:
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Window> window;
};
