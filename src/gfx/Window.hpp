#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "glutil.hpp"
#include "util.hpp"

class Window {
public:
    Window(unsigned int widthpx, unsigned int heightpx, std::string winTitle, bool maximised, bool resizable);
    ~Window();

    bool shouldWindowClose();
    void beginFrame();
    void endFrame();
    void processInput();
private:
    GLFWwindow* makeWindow(unsigned int widthpx, unsigned int heightpx, std::string& winTitle, bool maximised, bool resizable);

    unsigned int widthpx;
    unsigned int heightpx;
    std::string winTitle;
    bool maximised;
    bool resizable;
    GLFWwindow* window;
};