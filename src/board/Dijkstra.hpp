#pragma once

#include "util.hpp"
#include "Board.hpp"
#include "GridPiece.hpp"

/**
 * Singleton to house the Dijkstra Algorithm.
 */
class Dijkstra {
public:
    static void init(Board* b);
    static void iterate(Board* b);

private:
    // --- algorithm stuff ---
    std::vector<glm::vec2> directions {
        glm::vec2(0,  1), // Up
        glm::vec2(0, -1), // Down
        glm::vec2(-1, 0), // Left
        glm::vec2(1,  0)  // Right
    };
};