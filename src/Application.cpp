#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = new Window(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
}

Application::~Application() {
    delete window;
}

void Application::run() {
    std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>("Rectangle.vert", "Rectangle.frag", window->getWinWidth(), window->getWinHeight());
    std::unique_ptr<Rectangle> r1 = std::make_unique<Rectangle>(100.0f, 100.0f, Colors::LIGHT_PURPLE, sp);
    std::unique_ptr<Rectangle> r2 = std::make_unique<Rectangle>(100.0f, 100.0f, Colors::PURPLE, sp);

    int count = 0;
    while (!window->shouldWindowClose()) {
        window->beginFrame();
        window->setBgColor(Colors::DARK_GREY);

        count++;
        r1->translate(100, 100);
        r1->draw();

        r2->translate(500, 500);
        r2->draw();

        window->endFrame();
    }
}
