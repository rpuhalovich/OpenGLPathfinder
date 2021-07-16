#pragma once

#include "util.hpp"
#include "GridPiece.hpp"

enum class DijkstraState { running, finishFound, finishNotFound };

class Dijkstra {
public:
    Dijkstra(glm::vec2 gridDimensions);
    ~Dijkstra();

    void init(std::vector<std::vector<GridPiece*>>& grid);

    /**
     * \brief Relies on external while loop to complete all iterations.
     * \return state of the iteration, allowing for decision on what to do next.
     */
    DijkstraState iterate(std::vector<std::vector<GridPiece*>>& grid);

    void drawPath();
private:
    std::vector<GridPiece*> getGridVector(const std::vector<std::vector<GridPiece*>>& grid);
    GridPiece* getSmallestDistanceFromStart();
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

    glm::vec2 gridDimensions;

    GridPiece* finish;
};