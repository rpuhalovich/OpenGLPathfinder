#include "Board.hpp"
#include <random>
#include <algorithm>

Board::Board(float borderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor) :
    Rectangle(winWidth - borderSize * 2, winHeight - borderSize * 2, color)
{
    background = std::make_unique<Rectangle>(winWidth, winHeight, gridColor);
    Rectangle::translate(glm::vec2(borderSize, borderSize));

    // Allocating and translating the GridPieces.
    for (int x = 0; x < GRID_WIDTH; x++) {
        std::vector<GridPiece*> col;
        grid.push_back(col);
        for (int y = 0; y < GRID_HEIGHT; y++) {
            // push_back a new GridPiece to the end of the colum going from bottom to top.
            grid[x].push_back(new GridPiece(GRID_PIECE_SIZE, GRID_PIECE_SIZE, gridColor, GridPieceState::regular, glm::vec2(x, y)));

            // Then translate it to be at the appropriate x and y positions based on the boarder size.
            grid[x][y]->translate(glm::vec2(borderSize * 2 + ((GRID_PIECE_SIZE + borderSize) * x), borderSize * 2 + ((GRID_PIECE_SIZE + borderSize) * y)));
        }
    }

    // Setting start and finish GridPieces.
    int inDistance = 5;

    initStartLocation = glm::vec2(inDistance, GRID_HEIGHT / 2 + 1);
    startLocation = initStartLocation;

    initFinishLocation = glm::vec2(GRID_WIDTH - (inDistance + 1), GRID_HEIGHT / 2 + 1);
    finishLocation = initFinishLocation;

    grid[initStartLocation.x][initStartLocation.y]->setGridPieceState(GridPieceState::start);
    grid[initFinishLocation.x][initFinishLocation.y]->setGridPieceState(GridPieceState::finish);

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
    if (button == GLFW_KEY_R && action == GLFW_PRESS)
        resetBoard();
    if (button == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        dijkstra->init(grid);
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
            startLocation = gp->getBoardLocation();
            state = BoardState::idle;
        }
    } else if (state == BoardState::selectingFinish) {
        if (gp->getGridPieceState() == GridPieceState::regular || gp->getGridPieceState() == GridPieceState::obstacle) {
            selectedFinish->setGridPieceState(GridPieceState::regular);
            gp->setGridPieceState(GridPieceState::finish);
            finishLocation = gp->getBoardLocation();
            state = BoardState::idle;
        }
    }
}

void Board::rightClick(glm::vec2 location) {
    GridPiece* gp = getGridPieceAtLocation(location);
    if (!gp) return;

    if (gp->getGridPieceState() == GridPieceState::regular)
        gp->setGridPieceState(GridPieceState::obstacle);
}

void Board::draw() {
    background->draw();
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
    dijkstra->iterate(grid);
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

void Board::resetBoard() {
    clearObstacles();
    grid[startLocation.x][startLocation.y]->setGridPieceState(GridPieceState::regular);
    grid[initStartLocation.x][initStartLocation.y]->setGridPieceState(GridPieceState::start);
    startLocation = initStartLocation;

    grid[finishLocation.x][finishLocation.y]->setGridPieceState(GridPieceState::regular);
    grid[initFinishLocation.x][initFinishLocation.y]->setGridPieceState(GridPieceState::finish);
    finishLocation = initFinishLocation;
}

void Board::recursiveMaze() {
    clearObstacles();

    // TODO: Make work.
    //recursiveBacktracker(1, 1, 0);

    // Obstacle walls
    for (int x = 0; x < GRID_WIDTH; x++) {
        grid[x][0]->setGridPieceState(GridPieceState::obstacle);
        grid[x][GRID_HEIGHT - 1]->setGridPieceState(GridPieceState::obstacle);
    }

    for (int y = 0; y < GRID_HEIGHT; y++) {
        grid[0][y]->setGridPieceState(GridPieceState::obstacle);
        grid[GRID_WIDTH - 1][y]->setGridPieceState(GridPieceState::obstacle);
    }
}

void Board::recursiveBacktracker(int ox, int oy, int count) {
    if (count > 10) return;

    GridPieceState reg = GridPieceState::regular, obs = GridPieceState::obstacle;

    // To not have the Board::directions shuffled.
    std::vector<glm::vec2> localDirections {
        glm::vec2(0,  1), // Up
        glm::vec2(0, -1), // Down
        glm::vec2(-1, 0), // Left
        glm::vec2(1,  0)  // Right
    };

    std::shuffle(localDirections.begin(), localDirections.end(), std::default_random_engine{});

    for (auto const& d : localDirections) {
        glm::vec2 dir = glm::vec2(ox, oy) + d;
        if (glm::all(glm::greaterThan(dir, glm::vec2(0, 0))) && glm::all(glm::greaterThan(dir * glm::vec2(2, 2), glm::vec2(0, 0)))) {
            if (grid[dir.x][dir.y]->getGridPieceState() == reg && grid[dir.x * 2][dir.y * 2]->getGridPieceState() == reg) {
                grid[dir.x][dir.y]->setGridPieceState(obs);
                recursiveBacktracker(dir.x, dir.y, ++count);
            }
        }
    }
}

GridPiece* Board::getGridPieceAtLocation(glm::vec2 location) {
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            if (gridPiece->getBounds()->inBounds(location))
                return gridPiece;
    return nullptr;
}
