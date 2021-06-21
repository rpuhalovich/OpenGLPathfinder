#include "Window.hpp"

Window::Window(unsigned int widthpx, unsigned int heightpx, std::string winTitle, bool maximised, bool resizable) :
    widthpx(widthpx), heightpx(heightpx), winTitle(winTitle), maximised(maximised), resizable(resizable)
{
    window = makeWindow(widthpx, heightpx, winTitle, maximised, resizable);
    glfwMakeContextCurrent(window);
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::shouldWindowClose()
{
    return glfwWindowShouldClose(window);
}

void Window::beginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::endFrame()
{
}

GLFWwindow* Window::makeWindow(unsigned int widthpx, unsigned int heightpx, std::string& winTitle, bool maximised, bool resizable)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, maximised);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    if (!glfwInit()) errorExit("Failed to initialize GLFW!", -1);
    GLFWwindow* window = glfwCreateWindow(widthpx, heightpx, winTitle.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        errorExit("Failed to load window!", -1);
    }

    return window;
}
