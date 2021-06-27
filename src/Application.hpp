#pragma once

#include "Renderer.hpp"

/**
 * \brief A struct that can be set for different application properties.
 */
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

/**
 * Ideally this class wouldn't make direct reference to 
 * the renderer.
 */
class Application {
public:
    Application(ApplicationHints* ah);
    ~Application();

    void run();
private:
    Window* window;
};
