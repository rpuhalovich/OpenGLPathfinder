#include "Window.hpp"

Window::Window(unsigned int widthpx, unsigned int heightpx, std::string winTitle, bool maximised, bool resizable) :
    widthpx(widthpx), heightpx(heightpx), winTitle(winTitle), maximised(maximised), resizable(resizable)
{
    window = makeWindow(widthpx, heightpx, winTitle, maximised, resizable);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) errorExit("Failed to load OpenGL.", EXIT_FAILURE);
    std::cout << glGetString(GL_VERSION) << std::endl;
    stbi_set_flip_vertically_on_load(true);
}

Window::~Window() {
    glfwTerminate();
}

bool Window::shouldWindowClose() {
    return glfwWindowShouldClose(window);
}

void Window::beginFrame() {
    glc(glClear(GL_COLOR_BUFFER_BIT));
    processInput();
}

void Window::endFrame() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLFWwindow* Window::makeWindow(unsigned int widthpx, unsigned int heightpx, std::string& winTitle, bool maximised, bool resizable) {
    glfwInit();
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

    GLFWwindow* window = glfwCreateWindow(widthpx, heightpx, winTitle.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        errorExit("Failed to load window!", EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    return window;
}
