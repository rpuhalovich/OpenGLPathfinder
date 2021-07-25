#pragma once

#include <cstdlib>
#include <ctime>

static void errorExit(const char* m, int status) {
    printf("%s\n", m);
    exit(status);
}

static void initRand() {
    std::srand(std::time(nullptr));
}

static double nextRand() {
    return ((double)(rand() % 100)) / 100;
}

// from: https://stackoverflow.com/questions/9445327/fast-way-to-implement-pop-front-to-a-stdvector
template<typename T>
T pop_front(std::vector<T>& vec) {
    assert(!vec.empty());
    vec.front() = std::move(vec.back());
    T out = vec[0];
    vec.pop_back();
    return out;
}
