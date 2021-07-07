#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    // Note: Window should exist before the renderer as a context is needed.
    window = std::make_unique<Window>(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
    renderer->init(ah->winWidth, ah->winHeight);
}

Application::~Application() {

}

void Application::run() {
    std::shared_ptr<Board> board = std::make_shared<Board>(5.0f, window->getWinWidth(), window->getWinHeight(), Colors::DARK_GREY, Colors::XCODE_GREY);
    window->registerObserver(board.get());

    while (!window->shouldWindowClose()) {
        window->beginFrame();
        board->draw();
        window->endFrame();
    }
}
