#pragma once

#define NORMALIZE(x) x / 255.0f

namespace Colors {
    const glm::vec4 WHITE = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    const glm::vec4 BLACK = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    const glm::vec4 DARK_GREY = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    const glm::vec4 LIGHT_PURPLE = glm::vec4(NORMALIZE(242), NORMALIZE(201), NORMALIZE(242), 1.0f);
    const glm::vec4 PURPLE = glm::vec4(NORMALIZE(175), NORMALIZE(90), NORMALIZE(176), 1.0f);
}
