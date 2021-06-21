#include <GLFW/glfw3.h>
#include "Application.hpp"

int main(void)
{
    ApplicationHints* ah = new ApplicationHints();
    ah->winWidth = 1280;
    ah->winHeight = 720;
    ah->winTitle = std::string("Application");

    Application* a = new Application(*ah);
    a->run();
    delete a;
    return 0;
}