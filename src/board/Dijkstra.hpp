#pragma once

#include "util.hpp"
#include "GridPiece.hpp"

/**
 * Singleton to house the Dijkstra Algorithm.
 */
class Dijkstra {
public:
    Dijkstra();
    ~Dijkstra();

    void init(std::vector<std::vector<GridPiece*>>& grid);

    /**
     * \return true if the algorithm is complete.
     * Relies on external while loop to complete all iterations.
     */
    bool iterate(std::vector<std::vector<GridPiece*>>& grid);
private:
    std::vector<GridPiece*> getGridVector(const std::vector<std::vector<GridPiece*>>& grid);
    GridPiece* getSmallestDistanceFromStart(std::vector<GridPiece*>& unVisited);
    int calcDistance(GridPiece* gp);

    // --- algorithm stuff ---
    std::vector<glm::vec2> directions {
        glm::vec2(0,  1), // Up
        glm::vec2(0, -1), // Down
        glm::vec2(-1, 0), // Left
        glm::vec2(1,  0)  // Right
    };

    std::vector<GridPiece*> unVisited;
    std::vector<GridPiece*> visited;
};