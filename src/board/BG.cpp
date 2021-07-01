#include "BG.hpp"

BG::BG(float boarderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor) :
    Rectangle(winWidth - boarderSize, winHeight - boarderSize, color)
{
    Rectangle::translate(glm::vec2(boarderSize / 2, boarderSize / 2));

    for (int y = 0; y < GRID_HEIGHT; y++) {
        std::vector<GridPiece*> row;
        grid.push_back(row);
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y].push_back(new GridPiece(GRID_PIECE_SIZE, GRID_PIECE_SIZE, gridColor, GridPieceState::regular));
            grid[y][x]->translate(glm::vec2(boarderSize + ((GRID_PIECE_SIZE + GAP_SIZE) * x), boarderSize + ((GRID_PIECE_SIZE + GAP_SIZE) * y)));
        }
    }

    grid[0][0]->setGridPieceState(GridPieceState::start);
    grid[GRID_HEIGHT - 1][GRID_WIDTH - 1]->setGridPieceState(GridPieceState::finish);

    state = BGState::idle;
}

BG::~BG() {
    for (auto const& gridRow : grid) {
        for (auto const& gridPiece : gridRow) {
            delete gridPiece;
        }
    }
}

void BG::onUpdate(glm::vec2 location, int button, int action) {
    //Key events
    if (button == GLFW_KEY_C && action == GLFW_PRESS)
        clearObstacles();

    // Mouse button events
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        leftClick(location);

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        rightClick(location);
}

void BG::draw() {
    Rectangle::draw();
    for (auto const& gridRow : grid) {
        for (auto const& gridPiece : gridRow) {
            gridPiece->draw();
        }
    }

    double currentTime = glfwGetTime();
    int timeDelta = currentTime - lastTimeDelta;
    if (timeDelta >= 1.0f) {
        lastTimeDelta = glfwGetTime();
        iterate();
    }

}

void BG::iterate() {
    std::cout << "yeet" << std::endl;
}

void BG::clearObstacles() {
    for (auto const& gridRow : grid) {
        for (auto const& gridPiece : gridRow) {
            if (gridPiece->getGridPieceState() == GridPieceState::obstacle) {
                gridPiece->setGridPieceState(GridPieceState::regular);
            }
        }
    }
}

GridPiece* BG::getGridPieceAtLocation(glm::vec2 location) {
    // TODO: Such efficient.
    for (auto const& gridRow : grid) {
        for (auto const& gridPiece : gridRow) {
            if (gridPiece->getBounds()->inBounds(location)) {
                return gridPiece;
            }
        }
    }
    return nullptr;
}

void BG::leftClick(glm::vec2 location) {
    GridPiece* gp = getGridPieceAtLocation(location);
    if (!gp) return;

    if (state == BGState::idle) {
        if (gp->getGridPieceState() == GridPieceState::regular)
            gp->setGridPieceState(GridPieceState::obstacle);

        if (gp->getGridPieceState() == GridPieceState::start) {
            selectedStart = gp;
            gp->setGridPieceState(GridPieceState::startSelected);
            state = BGState::selectingStart;
        }

        if (gp->getGridPieceState() == GridPieceState::finish) {
            selectedFinish = gp;
            gp->setGridPieceState(GridPieceState::finishSelected);
            state = BGState::selectingFinish;
        }
    } else if (state == BGState::selectingStart) {
        if (gp->getGridPieceState() == GridPieceState::regular || gp->getGridPieceState() == GridPieceState::obstacle) {
            selectedStart->setGridPieceState(GridPieceState::regular);
            gp->setGridPieceState(GridPieceState::start);
            state = BGState::idle;
        }
    } else if (state == BGState::selectingFinish) {
        if (gp->getGridPieceState() == GridPieceState::regular || gp->getGridPieceState() == GridPieceState::obstacle) {
            selectedFinish->setGridPieceState(GridPieceState::regular);
            gp->setGridPieceState(GridPieceState::finish);
            state = BGState::idle;
        }
    }
}

void BG::rightClick(glm::vec2 location) {
    GridPiece* gp = getGridPieceAtLocation(location);
    if (!gp) return;

    if (gp->getGridPieceState() == GridPieceState::obstacle) {
        gp->setGridPieceState(GridPieceState::regular);
    }
}