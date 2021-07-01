#pragma once

#include "GridPiece.hpp"
#include "Rectangle.hpp"

// TODO: This is supposed to Board not BG...

enum class BGState { selectingStart, selectingFinish, running, idle };

class BG : public Rectangle {
public:
    BG(float boarderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor);
    ~BG();

    void onUpdate(glm::vec2 location, int button, int action) override;
    void updateGridPiece(GridPiece* gp);
    void draw() override;
    void clearObstacles();

    void rightClick(glm::vec2 location);
    void leftClick(glm::vec2 location);

    std::vector<std::vector<GridPiece*>> getGrid() { return grid; }
    GridPiece* getGridPieceAtLocation(glm::vec2 location);
private:
    glm::vec2 gridDimensions = glm::vec2(50, 50);
    std::vector<std::vector<GridPiece*>> grid;

    BGState state;
    GridPiece* selectedStart;
    GridPiece* selectedFinish;
};
