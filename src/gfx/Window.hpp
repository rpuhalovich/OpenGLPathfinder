#pragma once

#include "glutil.hpp"

#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "IEventSubject.hpp"
#include "IEventObserver.hpp"

#include "util.hpp"

// TODO: Next time make this a global singleton. Only ever going have one window.

class Window : public IEventSubject {
public:
    Window(float widthpx, float heightpx, std::string winTitle, bool maximised, bool resizable);
    ~Window();

    bool shouldWindowClose();
    void beginFrame();
    void endFrame();
    void processInput();
    void setBgColor(glm::vec4 color);

    void registerObserver(IEventObserver* observer) override;
    void register2DVecObservers(std::vector<std::vector<IEventObserver*>> grid);
    void unRegisterObserver(IEventObserver* observer) override;

    float getWinWidth() { return widthpx; }
    float getWinHeight() { return heightpx; }
    GLFWwindow* getWindow() { return window; }
private:
    GLFWwindow* makeWindow(unsigned int widthpx, unsigned int heightpx, std::string& winTitle, bool maximised, bool resizable);

    /**
     * Returns cursor position as glm::vec2 where y coord is adjusted to make the y = 0 the bottom of the window.
     */
    glm::vec2 getAdjustedCursorPosition();
    void notifyObserver(glm::vec2 location, int button, int action) override;

    const float widthpx;
    const float heightpx;
    std::string winTitle;
    bool maximised;
    bool resizable;
    GLFWwindow* window;

    std::vector<IEventObserver*> observers;

    int oldMouseState = GLFW_RELEASE;
    int oldKeyState = GLFW_RELEASE;
};
