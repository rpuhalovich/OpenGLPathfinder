#pragma once

#include "Renderer.hpp"

struct ApplicationHints {
    unsigned int winWidth;
    unsigned int winHeight;
    std::string winTitle;
    bool maximised;
    bool resizable;

    ApplicationHints() {
        winWidth = 1280;
        winHeight = 720;
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
    std::unique_ptr<Window> window;
};
