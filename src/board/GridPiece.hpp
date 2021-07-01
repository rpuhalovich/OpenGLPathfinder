#pragma once

#include "Rectangle.hpp"

// TODO: Separate these out into their own classes!
enum class GridPieceState { start, startSelected, finish, finishSelected, obstacle, regular };

class GridPiece : public Rectangle {
public:
    GridPiece(float width, float height, glm::vec4 color, GridPieceState state);
    ~GridPiece();

    void onUpdate(glm::vec2 location, int button, int action) override;
    void draw() override;

    void setGridPieceState(GridPieceState state);
    GridPieceState getGridPieceState() { return state; }
private:
    GridPieceState state;
    glm::vec4 initColor;
};
