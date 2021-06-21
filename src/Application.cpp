#include "Application.hpp"

Application::Application(const ApplicationHints& ah)
{
    window = new Window(ah.winWidth, ah.winHeight, ah.winTitle, ah.maximised, ah.resizable);
}

Application::~Application()
{
    delete window;
}

void Application::run()
{
    while (window->shouldWindowClose())
    {
        window->beginFrame();
    }
}
