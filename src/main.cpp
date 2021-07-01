#include "Application.hpp"

/**
 * --- Task List ---
 * TODO: Add uniform caching. Not necessary for our application because it's so simple but good practice though!
 * TODO: Make the parsing through graph a function pointer.
 * TODO: Make the 2D vector of GridPieces smart pointers instead of raw.
 */

int main(void) {
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    ApplicationHints* apphints = new ApplicationHints();
    apphints->winWidth = 1290.0f; // TODO: Make number of GridPieces a function of window width.
    apphints->winHeight = 715.0f;
    apphints->winTitle = std::string("OpenGL Pathfinder");
    apphints->maximised = false;
    apphints->resizable = false;

    Application* a = new Application(apphints);
    delete apphints;
    a->run();
    delete a;

#ifdef _MSC_VER
    _CrtDumpMemoryLeaks();
#endif
    return 0;
}
