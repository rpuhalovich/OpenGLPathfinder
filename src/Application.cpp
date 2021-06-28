#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = new Window(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
}

Application::~Application() {
    delete window;
}

void Application::run() {
    std::unique_ptr<Rectangle> r = std::make_unique<Rectangle>();

    // Run loop.
    while (!window->shouldWindowClose()) {
        window->beginFrame();

        // bg colour
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        r->draw();

        window->endFrame();
    }
}
