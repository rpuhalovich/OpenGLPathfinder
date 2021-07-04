#pragma once

#include "leakdetector.hpp"

#include <queue>

#include "util.hpp"
#include "GridPiece.hpp"
#include "Rectangle.hpp"

#define GRID_WIDTH 51
#define GRID_HEIGHT 28
#define GRID_PIECE_SIZE 20.0f

#define RAND_PROB 0.8f
#define DELTA_TIME 0.5f

enum class BoardState { selectingStart, selectingFinish, running, idle };

class Board : public Rectangle {
public:
    Board(float borderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor);
    ~Board();

    void onUpdate(glm::vec2 location, int button, int action) override;
    void draw() override;

    std::vector<std::vector<GridPiece*>> getGrid() { return grid; }
    GridPiece* getGridPieceAtLocation(glm::vec2 location);
private:
    struct DijkstraVertex;
    // --- methods ---
    void rightClick(glm::vec2 location);
    void leftClick(glm::vec2 location);

    /**
     * Completes an iteration of the algorithm based on a time delta.
     */
    void iterate();
    void clearObstacles();
    void randomObstacles();

    /**
     * Surrounds the grid with a wall of obstacles.
     */
    void obstacleWalls();
    void recursiveMaze();
    void recursiveBacktracker(int ox, int oy, int count);

    // --- members ---
    std::unique_ptr<Rectangle> background;

    glm::vec2 gridDimensions = glm::vec2(50, 50);
    std::vector<std::vector<GridPiece*>> grid;

    BoardState state;
    double lastTimeDelta = 0.0f;

    glm::vec2 startLocation;
    GridPiece* selectedStart;

    glm::vec2 finishLocation;
    GridPiece* selectedFinish;

    // --- algorithm stuff ---
    // recursiveBacktracking
    enum class direction { U, D, L, R };

    // Dijkstra's Algorithm
    struct DijkstraVertex {
        glm::vec2 location;
        int distanceFromStart;
    };

    void initDijkstra();
    void runDijkstra();

    glm::vec2 dijkstraDirections[4]{
        glm::vec2(0,  1), // Up
        glm::vec2(0, -1), // Down
        glm::vec2(-1,  0), // Left
        glm::vec2(1,  0)  // Right
    };

    DijkstraVertex* visited[GRID_WIDTH][GRID_HEIGHT];
    DijkstraVertex* unVisited[GRID_WIDTH][GRID_HEIGHT];

    std::shared_ptr<DijkstraVertex> getMin(const std::vector<std::shared_ptr<DijkstraVertex>>& unVisited);
};
