#pragma once

#include "leakdetector.hpp"

#include "util.hpp"
#include "GridPiece.hpp"
#include "Rectangle.hpp"
#include "Dijkstra.hpp"

#define GRID_WIDTH 51
#define GRID_HEIGHT 28
#define GRID_PIECE_SIZE 20.0f

#define RAND_PROB 0.8f
#define DELTA_TIME 0.01f

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
    // --- methods ---
    void rightClick(glm::vec2 location);
    void leftClick(glm::vec2 location);

    /**
     * Completes an iteration of the algorithm based on DELTA_TIME.
     */
    void iterate();
    void clearObstacles();
    void clearVisited();
    void clearBoard();
    void randomObstacles();
    void resetBoard();

    void recursiveMaze();
    void recursiveBacktracker(int ox, int oy, int count);

    // --- members ---
    std::unique_ptr<Rectangle> background;

    glm::vec2 gridDimensions = glm::vec2(50, 50);
    std::vector<std::vector<GridPiece*>> grid;

    BoardState state;
    double lastTimeDelta = 0.0f;

    glm::vec2 initStartLocation;
    glm::vec2 startLocation;
    GridPiece* selectedStart;

    glm::vec2 initFinishLocation;
    glm::vec2 finishLocation;
    GridPiece* selectedFinish;

    std::unique_ptr<Dijkstra> dijkstra;
};
