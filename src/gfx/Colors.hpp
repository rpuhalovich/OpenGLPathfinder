#pragma once

#include <glm/glm.hpp>

#include "glutil.hpp"
#include "util.hpp"

#define COLOR_RANGE 255

namespace Colors {
    float normalize(unsigned int value);

    const glm::vec4 WHITE = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    const glm::vec4 BLACK = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    const glm::vec4 PURPLE = glm::vec4(normalize(175), normalize(90), normalize(176), 1.0f);
}
