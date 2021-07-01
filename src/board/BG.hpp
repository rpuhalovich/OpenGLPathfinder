#pragma once

#include "GridPiece.hpp"
#include "Rectangle.hpp"



class BG : public Rectangle {
public:
    BG(float boarderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor);
    ~BG();

    void onUpdate(glm::vec2 location, int button, int action) override;
    void draw() override;

    std::vector<std::vector<GridPiece*>> getGrid() { return grid; }
private:
    glm::vec2 gridDimensions = glm::vec2(50, 50);
    std::vector<std::vector<GridPiece*>> grid;
};
