#include "Application.hpp"

Application::Application(ApplicationHints* ah) {
    window = std::make_unique<Window>(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
    std::shared_ptr<ShaderProgram> rectsp = std::make_shared<ShaderProgram>("Rectangle.vert", "Rectangle.frag", (float)window->getWinWidth(), (float)window->getWinHeight());
    Rectangle::setShader(rectsp);
}

Application::~Application() {

}

void Application::run() {
    std::unique_ptr<Rectangle> r1 = std::make_unique<Rectangle>(50.0f, 50.0f, Colors::LIGHT_PURPLE, RectangleType::square);
    std::unique_ptr<Rectangle> rbg = std::make_unique<Rectangle>(1260.0f, 700.0f, Colors::DARK_GREY, RectangleType::board);

    rbg->translate(10, 10);
    r1->translate(500, 500);
    window->registerObserver(r1.get());

    std::vector<Rectangle*> rectangles;
    int count = 0;
    for (int i = 0; i < 50; i++) {
        rectangles.push_back(new Rectangle(20.0f, 20.0f, Colors::PURPLE, RectangleType::square));
        rectangles[i]->translate(18 + count, 100);
        count += 25;
    }

    for (Rectangle* r : rectangles) window->registerObserver(r);

    while (!window->shouldWindowClose()) {
        window->beginFrame();
        window->setBgColor(Colors::LAVENDER);

        rbg->draw();
        r1->draw();

        for (auto const& r : rectangles) r->draw();

        window->endFrame();
    }

    for (Rectangle* r : rectangles) delete r;
}
