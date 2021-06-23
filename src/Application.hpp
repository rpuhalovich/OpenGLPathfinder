/**
 * This is the class that will handle the run loop.
 *
 * A facade class that ties together the system.
 */

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
        winHeight = 0;
        winWidth = 0;
        winTitle = std::string("Hello World");
        maximised = false;
        resizable = false;
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