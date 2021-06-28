#include "Colors.hpp"

namespace Colors {
    float Colors::normalize(unsigned int value) {
        if (value > COLOR_RANGE) errorExit("Invalid color range.", EXIT_FAILURE);
        return value / COLOR_RANGE;
    }
}
