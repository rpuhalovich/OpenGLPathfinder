#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = std::make_unique<Window>(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
    Rectangle::setShaderDimensions(ah->winWidth, ah->winHeight);
}

Application::~Application() {

}

void Application::run() {
    glm::vec4 gameColor = Colors::DARK_RED;
    
    std::unique_ptr<BG> bg = std::make_unique<BG>(10, window->getWinWidth(), window->getWinHeight(), Colors::DARK_GREY, gameColor);
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
