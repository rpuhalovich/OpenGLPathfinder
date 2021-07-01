#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = std::make_unique<Window>(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
    Rectangle::setShaderDimensions(ah->winWidth, ah->winHeight);
}

Application::~Application() {

}

void Application::run() {
    glm::vec4 gameColor = Colors::XCODE_GREY;

    std::shared_ptr<BG> bg = std::make_shared<BG>(10, window->getWinWidth(), window->getWinHeight(), Colors::DARK_GREY, gameColor);
    window->registerObserver(bg.get());
    for (auto const& gridRow : bg->getGrid()) {
        for (auto const& gridPiece : gridRow) {
            window->registerObserver(gridPiece);
        }
    }

    while (!window->shouldWindowClose()) {
        window->beginFrame();
        window->setBgColor(gameColor);

        bg->draw();

        window->endFrame();
    }
}
