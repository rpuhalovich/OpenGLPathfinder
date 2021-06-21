#pragma once

#include <glad/glad.h>

#ifdef __APPLE__
    #define ASSERT(x) if(!(x)) __builtin_trap();
#elif _MSC_VER
    #define ASSERT(x) if(!(x)) __debugbreak();
#else
    #define ASSERT(x) x
#endif

#ifdef DEB
    #define glc(x) glClearErrors(); x; ASSERT(glCheckError(#x, __FILE__, __LINE__))
#elif REL
    #define glc(x) x
#endif

void glClearErrors();
bool glCheckError(const char* function, const char* file, int line);
