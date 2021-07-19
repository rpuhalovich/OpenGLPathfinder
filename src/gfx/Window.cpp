#include "Window.hpp"

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Window::Window(float widthpx, float heightpx, std::string winTitle, bool maximised, bool resizable) :
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
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#elif _MSC_VER
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#elif __linux__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
    glfwSetKeyCallback(window, key_callback);

    return window;
}

static int s_key, s_KeyAction; // Nasty hack to get variable info out of the callback.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    s_key = key;
    s_KeyAction = action;
}

static int s_button, s_MouseAction; // Nasty hack to get variable info out of the callback.
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    s_button = button;
    s_MouseAction = action;
}

void Window::processInput() {
    // Key events
    int newKeyState = s_KeyAction; // This is a trick to get only a single click/key press registered.
    if (newKeyState == GLFW_RELEASE && oldKeyState == GLFW_PRESS) {
        if (s_key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);

        if (s_key == GLFW_KEY_1)
            notifyObserver(IGNORE_POS, GLFW_KEY_1, GLFW_PRESS);
        if (s_key == GLFW_KEY_2)
            notifyObserver(IGNORE_POS, GLFW_KEY_2, GLFW_PRESS);
        if (s_key == GLFW_KEY_C)
            notifyObserver(IGNORE_POS, GLFW_KEY_C, GLFW_PRESS);
        if (s_key == GLFW_KEY_R)
            notifyObserver(IGNORE_POS, GLFW_KEY_R, GLFW_PRESS);
        if (s_key == GLFW_KEY_S)
            notifyObserver(IGNORE_POS, GLFW_KEY_S, GLFW_PRESS);
        if (s_key == GLFW_KEY_SPACE)
            notifyObserver(IGNORE_POS, GLFW_KEY_SPACE, GLFW_PRESS);
    }
    oldKeyState = newKeyState;

    // Mouse button events
    int newMouseState = s_MouseAction;
    if (newMouseState == GLFW_RELEASE && oldMouseState == GLFW_PRESS) {
        if (s_button == GLFW_MOUSE_BUTTON_LEFT)
            notifyObserver(getAdjustedCursorPosition(), GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS);
    }
    oldMouseState = newMouseState;

    if (s_button == GLFW_MOUSE_BUTTON_RIGHT && newMouseState == GLFW_PRESS)
        notifyObserver(getAdjustedCursorPosition(), GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS);
    if (s_button == GLFW_MOUSE_BUTTON_MIDDLE && newMouseState == GLFW_PRESS)
        notifyObserver(getAdjustedCursorPosition(), GLFW_MOUSE_BUTTON_MIDDLE, GLFW_PRESS);
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

