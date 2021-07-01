#include "Window.hpp"

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Window::Window(unsigned int widthpx, unsigned int heightpx, std::string winTitle, bool maximised, bool resizable) :
    widthpx(widthpx), heightpx(heightpx), winTitle(winTitle), maximised(maximised), resizable(resizable)
{
    window = makeWindow(widthpx, heightpx, winTitle, maximised, resizable);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) errorExit("Failed to load OpenGL.", EXIT_FAILURE);

#ifdef DEBUG
    std::cout << glGetString(GL_VERSION) << std::endl;

    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif // DEBUG

    stbi_set_flip_vertically_on_load(true);
}

Window::~Window() {
    glfwTerminate();
}

glm::vec2 Window::getAdjustedCursorPosition() {
    double xpos, ypos;
    glfwGetCursorPos(this->getWindow(), &xpos, &ypos);
    return glm::vec2(xpos, this->getWinHeight() - ypos);
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
#ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif // DEBUG

    GLFWwindow* window = glfwCreateWindow(widthpx, heightpx, winTitle.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        errorExit("Failed to load window!", EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    return window;
}

int Window::getKeyPress() {
    // TODO: Surely there's a better way of doing this...
    int newKeyState = glfwGetKey(window, GLFW_KEY_1);
    if (newKeyState == GLFW_RELEASE && oldKeyState == GLFW_PRESS) {
        notifyObserver(IGNORE_POS, GLFW_KEY_1, GLFW_PRESS);
        oldKeyState = newKeyState;
    }

    oldKeyState = newKeyState;
    return -1;
}

static int s_button, s_action; // Nasty hack to get variable info out of the callback.
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    s_button = button;
    s_action = action;
}

void Window::processInput() {
    // Key events
    int key = getKeyPress();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        notifyObserver(IGNORE_POS, GLFW_KEY_C, GLFW_PRESS);
    if (glfwGetKey(window, key) == GLFW_PRESS)
        notifyObserver(IGNORE_POS, key, GLFW_PRESS);

    // This is a trick to get only a single click registered.
    int newMouseState = s_action;
    if (newMouseState == GLFW_RELEASE && oldMouseState == GLFW_PRESS) {
        // Mouse button events
        if (s_button == GLFW_MOUSE_BUTTON_LEFT)
            notifyObserver(getAdjustedCursorPosition(), GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS);
        if (s_button == GLFW_MOUSE_BUTTON_RIGHT)
            notifyObserver(getAdjustedCursorPosition(), GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS);
    }
    oldMouseState = newMouseState;
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

void Window::setBgColor(glm::vec4 color) {
    glc(glClearColor(color.x, color.y, color.z, color.w));
    glc(glClear(GL_COLOR_BUFFER_BIT));
}

void Window::registerObserver(IEventObserver* observer) {
    observers.push_back(observer);
}

void Window::unRegisterObserver(IEventObserver* observer) {
    // https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Window::notifyObserver(glm::vec2 location, int button, int action) {
    for (const auto& obs : observers) {
        obs->onUpdate(location, button, action);
    }
}

void Window::register2DVecObservers(std::vector<std::vector<IEventObserver*>> grid) {
    for (auto const& gridRow : grid) {
        for (auto const& gridPiece : gridRow) {
            registerObserver(gridPiece);
        }
    }
}

