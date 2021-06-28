#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = new Window(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
}

Application::~Application() {
    delete window;
}

void Application::run() {
    std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>("Rectangle.vert", "Rectangle.frag", window->getWinWidth(), window->getWinHeight());
    std::unique_ptr<Rectangle> r = std::make_unique<Rectangle>(100.0f, 100.0f, Colors::PURPLE, sp);

    while (!window->shouldWindowClose()) {
        window->beginFrame();

        window->setBgColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        r->draw();

        window->endFrame();
    }
}
