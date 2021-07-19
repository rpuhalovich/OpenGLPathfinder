#pragma once

#include "leakdetector.hpp"

#include <glad/glad.h>

#ifdef __APPLE__
    #define ASSERT(x) if(!(x)) __builtin_trap();
#elif _MSC_VER
    #define ASSERT(x) if(!(x)) __debugbreak();
#else
    #define ASSERT(x) x
#endif

#ifdef DEBUG
    #ifdef __APPLE__
        #define glc(x) glClearErrors(); x; ASSERT(glCheckError(#x, __FILE__, __LINE__))
    #endif

    #ifdef _WIN32  
        #define glc(x) x
    #endif
    
    #ifdef __linux__
        #define glc(x) x
    #endif
#elif RELEASE
    #define glc(x) x
#endif

#define glc(x) x

#define IGNORE_POS glm::vec2(-1, -1)

void glClearErrors();
bool glCheckError(const char* function, const char* file, int line);

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
