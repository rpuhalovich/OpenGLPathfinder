#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = std::make_unique<Window>(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
    Rectangle::setShaderDimensions(ah->winWidth, ah->winHeight);
}

Application::~Application() {

}

void Application::run() {
    std::unique_ptr<BG> bg = std::make_unique<BG>(1260, 700, Colors::DARK_GREY);
    bg->translate(glm::vec2(10, 10));
    for (auto const& g : bg->getGrid()) window->registerObserver(g);

    while (!window->shouldWindowClose()) {
        window->beginFrame();
        window->setBgColor(Colors::LAVENDER);

        bg->draw();

        window->endFrame();
    }
}
