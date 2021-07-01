#include "BG.hpp"

BG::BG(float boarderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor) :
    Rectangle(winWidth - boarderSize, winHeight - boarderSize, color)
{
    Rectangle::translate(glm::vec2(boarderSize / 2, boarderSize / 2));

    for (int y = 0; y < 28; y++) {
        std::vector<GridPiece*> row;
        grid.push_back(row);
        for (int x = 0; x < 51; x++) {
            grid[y].push_back(new GridPiece(20.0f, 20.0f, gridColor, GridPieceState::regular));
            grid[y][x]->translate(glm::vec2(10 + (25 * x), 10 + (25 * y)));
        }
    }

    grid[0][0]->setGridPieceState(GridPieceState::start);
    grid[27][50]->setGridPieceState(GridPieceState::finish);
}

BG::~BG() {
    for (auto const& gridRow : grid) {
        for (auto const& gridPiece : gridRow) {
            delete gridPiece;
        }
    }
}

void BG::onUpdate(glm::vec2 location, int button, int action) {

}

void BG::draw() {
    Rectangle::draw();
    for (auto const& gridRow : grid) {
        for (auto const& gridPiece : gridRow) {
            gridPiece->draw();
        }
    }
}
