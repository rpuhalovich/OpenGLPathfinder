#pragma once

#include <cstdlib>

static void errorExit(const char* m, int status) {
    printf("%s\n", m);
    exit(status);
}

static double nextRand() {
    return ((double)(rand() % 100)) / 100;
}