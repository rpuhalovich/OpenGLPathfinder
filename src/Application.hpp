#pragma once

#include "Renderer.hpp"
#include "Board.hpp"
#include "GridPiece.hpp"

struct ApplicationHints {
    float winWidth = 1280.0f;
    float winHeight = 720.0f;
    std::string winTitle = std::string("Hello World");
    bool maximised = true;
    bool resizable = true;
};

class Application {
public:
    Application(ApplicationHints* ah);
    ~Application();

    void run();
private:
    std::unique_ptr<Window> window;
};
