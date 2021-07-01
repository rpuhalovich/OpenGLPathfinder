#pragma once

#include "util.hpp"

#include "GridPiece.hpp"
#include "Rectangle.hpp"

// TODO: This is supposed to Board not BG...

#define GRID_WIDTH 51
#define GRID_HEIGHT 28
#define GRID_PIECE_SIZE 20.0f
#define GAP_SIZE 5.0f
#define RAND_PROB 0.8f
#define DELTA_TIME 0.5f

enum class BGState { selectingStart, selectingFinish, running, idle };

class BG : public Rectangle {
public:
    BG(float boarderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor);
    ~BG();

    void onUpdate(glm::vec2 location, int button, int action) override;
    void draw() override;

    /**
     * Completes an iteration of the algorithm based on a time delta.
     */
    void iterate();
    void clearObstacles();
    void randomObstacles();

    void rightClick(glm::vec2 location);
    void leftClick(glm::vec2 location);

    std::vector<std::vector<GridPiece*>> getGrid() { return grid; }
    GridPiece* getGridPieceAtLocation(glm::vec2 location);
private:
    glm::vec2 gridDimensions = glm::vec2(50, 50);
    std::vector<std::vector<GridPiece*>> grid;

    BGState state;
    double lastTimeDelta = 0.0f;
    GridPiece* selectedStart;
    GridPiece* selectedFinish;

    // temp stuff
    int lastx = 0;
    int lasty = 0;
};
