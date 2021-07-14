#pragma once

#include "leakdetector.hpp"

#define NORMALIZE(x) x / 255.0f

namespace Colors {
    const glm::vec4 WHITE = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    const glm::vec4 BLACK = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    const glm::vec4 DARK_GREY = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    const glm::vec4 LIGHT_GREY = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
    const glm::vec4 LESS_DARK_GREY = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);

    const glm::vec4 LIGHT_PURPLE = glm::vec4(NORMALIZE(242), NORMALIZE(201), NORMALIZE(242), 1.0f);
    const glm::vec4 PURPLE = glm::vec4(NORMALIZE(175), NORMALIZE(90), NORMALIZE(176), 1.0f);
    const glm::vec4 LAVENDER = glm::vec4(NORMALIZE(150), NORMALIZE(139), NORMALIZE(179), 1.0f);

    const glm::vec4 LIGHT_RED = glm::vec4(NORMALIZE(255), NORMALIZE(71), NORMALIZE(71), 1.0f);
    const glm::vec4 DARK_RED = glm::vec4(NORMALIZE(143), NORMALIZE(37), NORMALIZE(37), 1.0f);

    const glm::vec4 DARK_BLUE_GREY = glm::vec4(NORMALIZE(98), NORMALIZE(95), NORMALIZE(140), 1.0f);
    const glm::vec4 SPACE_CADET = glm::vec4(NORMALIZE(38), NORMALIZE(38), NORMALIZE(68), 1.0f);

    const glm::vec4 XCODE_GREY = glm::vec4(NORMALIZE(51), NORMALIZE(51), NORMALIZE(56), 1.0f);

    const glm::vec4 LIGHT_GREEN = glm::vec4(NORMALIZE(100), NORMALIZE(225), NORMALIZE(110), 1.0f);
    const glm::vec4 DARK_GREEN = glm::vec4(NORMALIZE(0), NORMALIZE(125), NORMALIZE(10), 1.0f);
}
