#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include "util.hpp"

class Window {
public:
    Window(unsigned int widthpx, unsigned int heightpx, std::string winTitle, bool maximised, bool resizable);
    ~Window();

    bool shouldWindowClose();
    void beginFrame();
    void endFrame();
private:
    // --- methods ---
    GLFWwindow* makeWindow(unsigned int widthpx, unsigned int heightpx, std::string& winTitle, bool maximised, bool resizable);

    // --- member variables ---
    unsigned int widthpx;
    unsigned int heightpx;
    std::string winTitle;
    bool maximised;
    bool resizable;
    GLFWwindow* window;
};