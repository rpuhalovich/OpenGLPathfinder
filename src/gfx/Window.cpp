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

static int s_button, s_action;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    s_button = button;
    s_action = action;
}

void Window::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        notifyObserver(IGNORE_POS, GLFW_KEY_Y, GLFW_PRESS);
    }

    if (s_button == GLFW_MOUSE_BUTTON_LEFT && s_action == GLFW_PRESS) {
        glm::vec2 cursorpos = getAdjustedCursorPosition();
        std::cout << "xpos: " << cursorpos.x << " ypos: " << cursorpos.y << std::endl;
        notifyObserver(glm::vec2(cursorpos.x, cursorpos.y), GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS);
    }
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
        obs->OnUpdate(location, button, action);
    }
}
