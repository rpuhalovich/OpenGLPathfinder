#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = std::make_unique<Window>(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);

    // TODO: abstract to Renderer initialization method call of some sort.
    Rectangle::setShaderDimensions(ah->winWidth, ah->winHeight);
}

Application::~Application() {

}

void Application::run() {
    glm::vec4 gameColor = Colors::XCODE_GREY;

    std::shared_ptr<Board> bg = std::make_shared<Board>(5.0f, window->getWinWidth(), window->getWinHeight(), Colors::DARK_GREY, gameColor);
    window->registerObserver(bg.get());
    for (auto const& gridRow : bg->getGrid())
        for (auto const& gridPiece : gridRow)
            window->registerObserver(gridPiece);

    while (!window->shouldWindowClose()) {
        window->beginFrame();
        window->setBgColor(gameColor);

        bg->draw();

        window->endFrame();
    }
}
