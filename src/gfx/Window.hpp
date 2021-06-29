#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Event.hpp"

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
    void setBgColor(glm::vec4 color);

    unsigned int getWinWidth() { return widthpx; }
    unsigned int getWinHeight() { return heightpx; }
private:
    GLFWwindow* makeWindow(unsigned int widthpx, unsigned int heightpx, std::string& winTitle, bool maximised, bool resizable);

    const unsigned int widthpx;
    const unsigned int heightpx;
    std::string winTitle;
    bool maximised;
    bool resizable;
    GLFWwindow* window;
};
