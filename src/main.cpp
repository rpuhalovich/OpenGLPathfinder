#include <GLFW/glfw3.h>
#include "Application.hpp"

int main(void)
{
    ApplicationHints* apphints = new ApplicationHints();
    apphints->winWidth = 1280;
    apphints->winHeight = 720;
    apphints->winTitle = std::string("Application");

    Application* a = new Application(apphints);
    delete apphints;
    a->run();
    delete a;
    return 0;
}