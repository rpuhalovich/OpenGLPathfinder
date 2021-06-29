#pragma once

#include <glm/glm.hpp>

#include "glutil.hpp"
#include "util.hpp"

#define NORMALIZE(x) x / 255.0f

namespace Colors {
    const glm::vec4 WHITE = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    const glm::vec4 BLACK = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    const glm::vec4 PURPLE = glm::vec4(NORMALIZE(175), NORMALIZE(90), NORMALIZE(176), 1.0f);
}
