#include "GridPiece.hpp"

GridPiece::GridPiece(float width, float height, glm::vec4 color, GridPieceState state, glm::vec2 boardLocation) :
    Rectangle(width, height, color), gridColor(color), boardLocation(boardLocation), prev(nullptr)
{
    setGridPieceState(state);
}

GridPiece::~GridPiece() {

}

void GridPiece::onUpdate(glm::vec2 location, int button, int action) {

}

void GridPiece::draw() {
    Rectangle::draw();
}

void GridPiece::setGridPieceState(GridPieceState state) {
    this->state = state;
    switch (state) {
        case GridPieceState::start: {
            Rectangle::changeColor(Colors::LIGHT_GREEN);
            break;
        }
        case GridPieceState::startSelected: {
            Rectangle::changeColor(Colors::DARK_GREEN);
            break;
        }
        case GridPieceState::finish: {
            Rectangle::changeColor(Colors::LIGHT_RED);
            break;
        }
        case GridPieceState::finishSelected: {
            Rectangle::changeColor(Colors::DARK_RED);
            break;
        }
        case GridPieceState::obstacle: {
            Rectangle::changeColor(Colors::WHITE);
            break;
        }
        case GridPieceState::visiting: {
            Rectangle::changeColor(Colors::DARK_BLUE_GREY);
            break;
        }
        case GridPieceState::visited: {
            Rectangle::changeColor(Colors::LIGHT_PURPLE);
            break;
        }
        case GridPieceState::path: {
            Rectangle::changeColor(Colors::DARK_GREEN);
            break;
        }
        case GridPieceState::regular: {
            Rectangle::changeColor(gridColor);
            break;
        }
    }
}
