#include "Board.hpp"
#include <random>
#include <algorithm>

Board::Board(float borderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor) :
    Rectangle(winWidth - borderSize, winHeight - borderSize, color)
{
    Rectangle::translate(glm::vec2(borderSize / 2, borderSize / 2));

    // Allocating and translating the GridPieces.
    for (int x = 0; x < GRID_WIDTH; x++) {
        std::vector<GridPiece*> col;
        grid.push_back(col);
        for (int y = 0; y < GRID_HEIGHT; y++) {
            // push_back a new GridPiece to the end of the colum going from bottom to top.
            grid[x].push_back(new GridPiece(GRID_PIECE_SIZE, GRID_PIECE_SIZE, gridColor, GridPieceState::regular));

            // Then translate it to be at the appropriate x and y positions based on the boarder size.
            grid[x][y]->translate(glm::vec2(borderSize + ((GRID_PIECE_SIZE + borderSize / 2) * x), borderSize + ((GRID_PIECE_SIZE + borderSize / 2) * y)));
        }
    }

    // Setting start and finish GridPieces.
    int inDistance = 5;
    grid[inDistance][GRID_HEIGHT / 2 + 1]->setGridPieceState(GridPieceState::start);
    grid[GRID_WIDTH - (inDistance + 1)][GRID_HEIGHT / 2 + 1]->setGridPieceState(GridPieceState::finish);

    state = BoardState::idle;
}

Board::~Board() {
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            delete gridPiece;
}

void Board::onUpdate(glm::vec2 location, int button, int action) {
    // Key events
    if (button == GLFW_KEY_1 && action == GLFW_PRESS)
        randomObstacles();
    if (button == GLFW_KEY_2 && action == GLFW_PRESS)
        recursiveMaze();
    if (button == GLFW_KEY_C && action == GLFW_PRESS)
        clearObstacles();
    if (button == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        initDijkstra();
        state != BoardState::running ? state = BoardState::running : state = BoardState::idle;
    }

    // Mouse button events
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        leftClick(location);
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        rightClick(location);
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        GridPiece* gp = getGridPieceAtLocation(location);
        if (!gp) return;

        if (gp->getGridPieceState() == GridPieceState::obstacle)
            gp->setGridPieceState(GridPieceState::regular);
    }
}

void Board::leftClick(glm::vec2 location) {
    GridPiece* gp = getGridPieceAtLocation(location);
    if (!gp) return;

    if (state == BoardState::idle) {
        if (gp->getGridPieceState() == GridPieceState::regular) {
            gp->setGridPieceState(GridPieceState::obstacle);
        }
        else if (gp->getGridPieceState() == GridPieceState::obstacle) {
            gp->setGridPieceState(GridPieceState::regular);
        }

        if (gp->getGridPieceState() == GridPieceState::start) {
            selectedStart = gp;
            gp->setGridPieceState(GridPieceState::startSelected);
            state = BoardState::selectingStart;
        }

        if (gp->getGridPieceState() == GridPieceState::finish) {
            selectedFinish = gp;
            gp->setGridPieceState(GridPieceState::finishSelected);
            state = BoardState::selectingFinish;
        }
    } else if (state == BoardState::selectingStart) {
        if (gp->getGridPieceState() == GridPieceState::regular || gp->getGridPieceState() == GridPieceState::obstacle) {
            selectedStart->setGridPieceState(GridPieceState::regular);
            gp->setGridPieceState(GridPieceState::start);
            state = BoardState::idle;
        }
    } else if (state == BoardState::selectingFinish) {
        if (gp->getGridPieceState() == GridPieceState::regular || gp->getGridPieceState() == GridPieceState::obstacle) {
            selectedFinish->setGridPieceState(GridPieceState::regular);
            gp->setGridPieceState(GridPieceState::finish);
            state = BoardState::idle;
        }
    }
}

void Board::rightClick(glm::vec2 location) {
    GridPiece* gp = getGridPieceAtLocation(location);
    if (!gp) return;

    if (gp->getGridPieceState() == GridPieceState::regular) {
        gp->setGridPieceState(GridPieceState::obstacle);
    }
}

void Board::draw() {
    Rectangle::draw();
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            gridPiece->draw();

    // If the Board is in running state, it will iterate the algorithm every DELTA_TIME
    if (state == BoardState::running) {
        double currentTime = glfwGetTime();
        double timeDelta = currentTime - lastTimeDelta;
        if (timeDelta >= DELTA_TIME) {
            lastTimeDelta = currentTime;
            iterate();
        }
    }
}

void Board::iterate() {
    std::cout << "yeet" << std::endl;
}

void Board::initDijkstra() {
    visited.clear();

    //for (int x = 0; x < GRID_WIDTH; x++) {
    //    for (int y = 0; y < GRID_HEIGHT; y++) {
    //        std::shared_ptr<DijkstraVertex> temp = std::make_shared<DijkstraVertex>(glm::vec2(x, y), this);
    //        unVisited.push_back(temp);
    //    }
    //}
}

void Board::runDijkstra() {
    if (unVisited.size() > 0) {
        // Get Min
    }
}

void Board::clearObstacles() {
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            if (gridPiece->getGridPieceState() == GridPieceState::obstacle)
                gridPiece->setGridPieceState(GridPieceState::regular);
}

void Board::randomObstacles() {
    clearObstacles();
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            if (gridPiece->getGridPieceState() == GridPieceState::regular && nextRand() >= RAND_PROB)
                gridPiece->setGridPieceState(GridPieceState::obstacle);
}

void Board::obstacleWalls() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        grid[x][0]->setGridPieceState(GridPieceState::obstacle);
        grid[x][GRID_HEIGHT - 1]->setGridPieceState(GridPieceState::obstacle);
    }

    for (int y = 0; y < GRID_HEIGHT; y++) {
        grid[0][y]->setGridPieceState(GridPieceState::obstacle);
        grid[GRID_WIDTH - 1][y]->setGridPieceState(GridPieceState::obstacle);
    }
}

void Board::recursiveMaze() {
    clearObstacles();
    // TODO: Make work.
    //recursiveBacktracker(1, 1, 0);
    obstacleWalls();
}

void Board::recursiveBacktracker(int ox, int oy, int count) {
    if (count > 17) return;

    GridPieceState reg = GridPieceState::regular, obs = GridPieceState::obstacle;

    std::vector<direction> directions = { direction::U, direction::D, direction::L, direction::R };
    auto rng = std::default_random_engine{};
    std::shuffle(directions.begin(), directions.end(), rng);

    GridPiece* previous;

    for (auto const& d : directions) {
        switch (d) {
            case direction::U: {
                int newDir = oy + 1;
                if (newDir < GRID_HEIGHT && grid[ox][newDir]->getGridPieceState() == reg) {
                    grid[ox][newDir]->setGridPieceState(obs);
                    recursiveBacktracker(ox, newDir, ++count);
                }
                break;
            } case direction::D: {
                int newDir = oy - 1;
                if (newDir >= 0 && grid[ox][newDir]->getGridPieceState() == reg) {
                    grid[ox][newDir - 1]->setGridPieceState(obs);
                    recursiveBacktracker(ox, newDir, ++count);
                }
                break;
            } case direction::L: {
                int newDir = ox - 1;
                if (newDir >= 0 && grid[newDir][oy]->getGridPieceState() == reg) {
                    grid[newDir][oy]->setGridPieceState(obs);
                    recursiveBacktracker(newDir, oy, ++count);
                }
                break;
            } case direction::R: {
                int newDir = ox + 1;
                if (newDir < GRID_WIDTH && grid[newDir][oy]->getGridPieceState() == reg) {
                    grid[newDir][oy]->setGridPieceState(obs);
                    recursiveBacktracker(newDir, oy, ++count);
                }
                break;
            }
        }
    }
}

GridPiece* Board::getGridPieceAtLocation(glm::vec2 location) {
    // TODO: Such efficient.
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            if (gridPiece->getBounds()->inBounds(location))
                return gridPiece;
    return nullptr;
}
