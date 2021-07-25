#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    RendererHints rh;

    rh.maximised = ah->maximised;
    rh.resizable = ah->resizable;
    rh.winTitle = ah->winTitle;
    rh.winHeight = ah->winHeight;
    rh.winWidth = ah->winWidth;

    window = Renderer::init(&rh);
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
