#include "BG.hpp"

BG::BG(float boarderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor) :
    Rectangle(winWidth - boarderSize, winHeight - boarderSize, color)
{
    Rectangle::translate(glm::vec2(boarderSize / 2, boarderSize / 2));

    for (int x = 0; x < GRID_WIDTH; x++) {
        std::vector<GridPiece*> col;
        grid.push_back(col);
        for (int y = 0; y < GRID_HEIGHT; y++) {
            // push_back a new GridPiece to the end of the colum going from bottom to top.
            grid[x].push_back(new GridPiece(GRID_PIECE_SIZE, GRID_PIECE_SIZE, gridColor, GridPieceState::regular));

            // Then translate it to be at the appropriate x and y positions based on the boarder size.
            grid[x][y]->translate(glm::vec2(boarderSize + ((GRID_PIECE_SIZE + boarderSize / 2) * x), boarderSize + ((GRID_PIECE_SIZE + boarderSize / 2) * y)));
        }
    }

    int inDistance = 5;
    grid[inDistance][GRID_HEIGHT / 2 + 1]->setGridPieceState(GridPieceState::start);
    grid[GRID_WIDTH - (inDistance + 1)][GRID_HEIGHT / 2 + 1]->setGridPieceState(GridPieceState::finish);

    state = BGState::idle;
}

BG::~BG() {
    for (auto const& gridCol : grid) {
        for (auto const& gridPiece : gridCol) {
            delete gridPiece;
        }
    }
}

void BG::onUpdate(glm::vec2 location, int button, int action) {
    // Key events
    if (button == GLFW_KEY_C && action == GLFW_PRESS)
        clearObstacles();
    if (button == GLFW_KEY_1 && action == GLFW_PRESS)
        randomObstacles();
    if (button == GLFW_KEY_2 && action == GLFW_PRESS)
        recursiveMaze();
    if (button == GLFW_KEY_SPACE && action == GLFW_PRESS)
        state != BGState::running ? state = BGState::running : state = BGState::idle;

    // Mouse button events
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        leftClick(location);

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        rightClick(location);
}

void BG::draw() {
    Rectangle::draw();
    for (auto const& gridCol : grid) {
        for (auto const& gridPiece : gridCol) {
            gridPiece->draw();
        }
    }

    // If the BG is in running state, it will iterate the algorithm every DELTA_TIME
    if (state == BGState::running) {
        double currentTime = glfwGetTime();
        double timeDelta = currentTime - lastTimeDelta;
        if (timeDelta >= DELTA_TIME) {
            lastTimeDelta = currentTime;
            iterate();
        }
    }
}

void BG::iterate() {
    std::cout << "yeet" << std::endl;
}

void BG::clearObstacles() {
    for (auto const& gridCol : grid) {
        for (auto const& gridPiece : gridCol) {
            if (gridPiece->getGridPieceState() == GridPieceState::obstacle) {
                gridPiece->setGridPieceState(GridPieceState::regular);
            }
        }
    }
}

void BG::randomObstacles() {
    clearObstacles();
    for (auto const& gridCol : grid) {
        for (auto const& gridPiece : gridCol) {
            if (gridPiece->getGridPieceState() == GridPieceState::regular && nextRand() >= RAND_PROB)
                gridPiece->setGridPieceState(GridPieceState::obstacle);
        }
    }
}

void BG::recursiveMaze() {
    clearObstacles();
    obstacleWalls();
}

GridPiece* BG::getGridPieceAtLocation(glm::vec2 location) {
    // TODO: Such efficient.
    for (auto const& gridCol : grid) {
        for (auto const& gridPiece : gridCol) {
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

void BG::obstacleWalls() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        grid[x][0]->setGridPieceState(GridPieceState::obstacle);
        grid[x][GRID_HEIGHT - 1]->setGridPieceState(GridPieceState::obstacle);
    }

    for (int y = 0; y < GRID_HEIGHT; y++) {
        grid[0][y]->setGridPieceState(GridPieceState::obstacle);
        grid[GRID_WIDTH - 1][y]->setGridPieceState(GridPieceState::obstacle);
    }
}

void BG::rightClick(glm::vec2 location) {
    GridPiece* gp = getGridPieceAtLocation(location);
    if (!gp) return;

    if (gp->getGridPieceState() == GridPieceState::obstacle) {
        gp->setGridPieceState(GridPieceState::regular);
    }
}
