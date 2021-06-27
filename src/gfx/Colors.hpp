#pragma once

#include <glm/glm.hpp>

#include "glutil.hpp"
#include "util.hpp"

#define COLOR_RANGE 255

struct Colors {
public:
    const glm::vec4 WHITE = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    const glm::vec4 BLACK = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

private:
    /**
     * \brief Converts the inputted color range value to a normalized value for OpenGL.
     */
    float normalize(unsigned int value) {
        if (value > COLOR_RANGE) errorExit("Invalid color range.", EXIT_FAILURE);
        return value / COLOR_RANGE;
    }
};