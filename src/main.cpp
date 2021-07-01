#include "Application.hpp"

/**
 * --- Task List ---
 * TODO: Add uniform caching. Not necessary for our application because it's so simple but good practice though!
 */

int main(void) {
    ApplicationHints* apphints = new ApplicationHints();
    apphints->winWidth = 1290; // TODO: Make number of GridPieces a function of window width.
    apphints->winHeight = 715;
    apphints->winTitle = std::string("OpenGL Pathfinder");
    apphints->maximised = false;
    apphints->resizable = false;

    Application* a = new Application(apphints);
    delete apphints;
    a->run();
    delete a;
    return 0;
}
