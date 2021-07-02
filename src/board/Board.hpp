#pragma once

#include "leakdetector.hpp"

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
    Board(float boarderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor);
    ~Board();

    void onUpdate(glm::vec2 location, int button, int action) override;
    void draw() override;

    std::vector<std::vector<GridPiece*>> getGrid() { return grid; }
    GridPiece* getGridPieceAtLocation(glm::vec2 location);
private:
    // --- algorithm stuff ---
    // recursiveBacktracking
    enum class direction { U, D, L, R };

    // --- methods ---
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

    void rightClick(glm::vec2 location);
    void leftClick(glm::vec2 location);

    // --- members ---
    glm::vec2 gridDimensions = glm::vec2(50, 50);
    std::vector<std::vector<GridPiece*>> grid;

    BoardState state;
    double lastTimeDelta = 0.0f;

    glm::vec2 startLocation;
    GridPiece* selectedStart;

    glm::vec2 finishLocation;
    GridPiece* selectedFinish;

    // temp stuff
    int lastx = 0;
    int lasty = 0;
};
