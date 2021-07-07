#pragma once

#include "leakdetector.hpp"
#include "Rectangle.hpp"

enum class GridPieceState {
    start,
    startSelected,
    finish,
    finishSelected,
    obstacle,
    visiting,
    visited,
    path,
    regular
};

class GridPiece : public Rectangle {
public:
    GridPiece(float width, float height, glm::vec4 color, GridPieceState state, glm::vec2 boardLocation);
    ~GridPiece();

    void init();

    void onUpdate(glm::vec2 location, int button, int action) override;
    void draw() override;

    void setGridPieceState(GridPieceState state);
    GridPieceState getGridPieceState() { return state; }

    glm::vec2 getBoardLocation() { return boardLocation; }

    void setDistanceFromStart(int distance) { distanceFromStart = distance; }
    int getDistanceFromStart() { return distanceFromStart; }
    GridPiece* getPrev() { return prev; }
    void setPrev(GridPiece* prev) { this->prev = prev; }
private:
    // Dijkstra's Stuff
    glm::vec2 boardLocation;
    GridPiece* prev;
    int distanceFromStart;

    GridPieceState state;
    glm::vec4 gridColor;
};
