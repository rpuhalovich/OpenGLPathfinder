#include "Application.hpp"

Application::Application(ApplicationHints* ah)
{
    window = new Window(ah->winWidth, ah->winHeight, ah->winTitle, ah->maximised, ah->resizable);
}

Application::~Application()
{
    delete window;
}

void Application::run()
{
    while (!window->shouldWindowClose())
    {
        window->beginFrame();

        // Add code.
        unsigned int vbo;
        glGenBuffers(1, &vbo);

        window->endFrame();
    }
}
