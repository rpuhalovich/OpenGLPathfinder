#include "Application.hpp"

/**
 * --- Task List ---
 * TODO: Add caching. Not necessary for our application because it's so simple but good practice though!
 */

int main(void) {
    ApplicationHints* apphints = new ApplicationHints();
    apphints->winWidth = 1280;
    apphints->winHeight = 720;
    apphints->winTitle = std::string("Application");
    apphints->maximised = false;
    apphints->resizable = false;

    Application* a = new Application(apphints);
    delete apphints;
    a->run();
    delete a;
    return 0;
}
