#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = std::make_unique<Window>(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
    Rectangle::setShaderDimensions(ah->winWidth, ah->winHeight);
}

Application::~Application() {

}

void Application::run() {
    std::unique_ptr<BG> bg = std::make_unique<BG>(10, window->getWinWidth(), window->getWinHeight(), Colors::DARK_GREY);
    for (auto const& gridRow : bg->getGrid()) {
        for (auto const& gridPiece : gridRow) {
            window->registerObserver(gridPiece);
        }
    }

    while (!window->shouldWindowClose()) {
        window->beginFrame();
        window->setBgColor(Colors::PURPLE);

        bg->draw();

        window->endFrame();
    }
}
