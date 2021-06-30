#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "IEventSubject.hpp"
#include "IEventObserver.hpp"

#include "glutil.hpp"
#include "util.hpp"

#define IGNORE_POS glm::vec2(-1, -1)

class Window : public IEventSubject {
public:
    Window(unsigned int widthpx, unsigned int heightpx, std::string winTitle, bool maximised, bool resizable);
    ~Window();

    bool shouldWindowClose();
    void beginFrame();
    void endFrame();
    void processInput();
    void setBgColor(glm::vec4 color);

    void registerObserver(IEventObserver* observer) override;
    void unRegisterObserver(IEventObserver* observer) override;

    unsigned int getWinWidth() { return widthpx; }
    unsigned int getWinHeight() { return heightpx; }
    GLFWwindow* getWindow() { return window; }
private:
    GLFWwindow* makeWindow(unsigned int widthpx, unsigned int heightpx, std::string& winTitle, bool maximised, bool resizable);
    glm::vec2 getAdjustedCursorPosition();
    void notifyObserver(glm::vec2 location, int button, int action) override;

    const unsigned int widthpx;
    const unsigned int heightpx;
    std::string winTitle;
    bool maximised;
    bool resizable;
    GLFWwindow* window;

    std::vector<IEventObserver*> observers;
};
