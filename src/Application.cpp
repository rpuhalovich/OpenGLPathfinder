#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = new Window(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
    std::shared_ptr<ShaderProgram> rectsp = std::make_shared<ShaderProgram>("Rectangle.vert", "Rectangle.frag", (float)window->getWinWidth(), (float)window->getWinHeight());
    Rectangle::setShader(rectsp);
}

Application::~Application() {
    delete window;
}

void Application::run() {
    std::unique_ptr<Rectangle> r1 = std::make_unique<Rectangle>(100.0f, 100.0f, Colors::LIGHT_PURPLE);
    std::unique_ptr<Rectangle> r2 = std::make_unique<Rectangle>(100.0f, 100.0f, Colors::PURPLE);

    int count = 0;
    while (!window->shouldWindowClose()) {
        window->beginFrame();
        window->setBgColor(Colors::DARK_RED);

        //count++;
        r1->translate(100 + count, 100);
        r1->draw();

        r2->translate(500, 500 - count);
        r2->draw();

        window->endFrame();
    }
}
