#include "Board.hpp"
#include <random>
#include <algorithm>
#include <stack>

Board::Board(float borderSize, float winWidth, float winHeight, glm::vec4 color, glm::vec4 gridColor) :
    Rectangle(winWidth - borderSize * 2, winHeight - borderSize * 2, color), 
    background(std::make_unique<Rectangle>(winWidth, winHeight, gridColor)),
    state(BoardState::idle),
    dijkstra(std::make_unique<Dijkstra>(glm::vec2(GRID_WIDTH, GRID_HEIGHT)))
{
    Rectangle::translate(glm::vec2(borderSize, borderSize));

    // Allocating and translating the GridPieces.
    for (int x = 0; x < GRID_WIDTH; x++) {
        std::vector<GridPiece*> col;
        grid.push_back(col);
        for (int y = 0; y < GRID_HEIGHT; y++) {
            // push_back a new GridPiece to the end of the colum going from bottom to top.
            grid[x].push_back(new GridPiece(GRID_PIECE_SIZE, GRID_PIECE_SIZE, gridColor, GridPieceState::unVisited, glm::vec2(x, y)));

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
}

Board::~Board() {
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            delete gridPiece;
}

void Board::onUpdate(glm::vec2 location, int button, int action) {
    // Key events
    if (state != BoardState::running) {
        if (button == GLFW_KEY_1 && action == GLFW_PRESS) {
            clearVisited();
            randomObstacles();
        }
        if (button == GLFW_KEY_2 && action == GLFW_PRESS) {
            clearVisited();
            recursiveMaze();
        }
        if (button == GLFW_KEY_C && action == GLFW_PRESS) {
            clearVisited();
            clearObstacles();
        }
        if (button == GLFW_KEY_R && action == GLFW_PRESS) {
            clearVisited();
            resetBoard();
        }
    }

    if (button == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        clearVisited();
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
            gp->setGridPieceState(GridPieceState::unVisited);
    }
}

void Board::leftClick(glm::vec2 location) {
    GridPiece* gp = getGridPieceAtLocation(location);
    if (!gp) return;

    if (state == BoardState::idle) {
        if (gp->getGridPieceState() == GridPieceState::unVisited) {
            gp->setGridPieceState(GridPieceState::obstacle);
        } else if (gp->getGridPieceState() == GridPieceState::obstacle) {
            gp->setGridPieceState(GridPieceState::unVisited);
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
        if (gp->getGridPieceState() == GridPieceState::unVisited || gp->getGridPieceState() == GridPieceState::obstacle) {
            selectedStart->setGridPieceState(GridPieceState::unVisited);
            gp->setGridPieceState(GridPieceState::start);
            startLocation = gp->getBoardLocation();
            state = BoardState::idle;
        }
    } else if (state == BoardState::selectingFinish) {
        if (gp->getGridPieceState() == GridPieceState::unVisited || gp->getGridPieceState() == GridPieceState::obstacle) {
            selectedFinish->setGridPieceState(GridPieceState::unVisited);
            gp->setGridPieceState(GridPieceState::finish);
            finishLocation = gp->getBoardLocation();
            state = BoardState::idle;
        }
    }
}

void Board::rightClick(glm::vec2 location) {
    GridPiece* gp = getGridPieceAtLocation(location);
    if (!gp) return;

    if (state == BoardState::idle) {
        if (gp->getGridPieceState() == GridPieceState::unVisited)
            gp->setGridPieceState(GridPieceState::obstacle);
    }
}

bool Board::calcTimeDelta(float deltaTime) {
    double currentTime = glfwGetTime();
    double timeDelta = currentTime - lastTimeDelta;
    if (timeDelta >= deltaTime) {
        lastTimeDelta = currentTime;
        return true;
    }
    return false;
}

void Board::draw() {
    background->draw();
    Rectangle::draw();
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            gridPiece->draw();

    // If the Board is in running state, it will iterate the algorithm every DELTA_TIME
    if (state == BoardState::running) {
        if (calcTimeDelta(DELTA_TIME)) {
            iterate();
        }
    }
}

void Board::iterate() {
    if (dijkstra->iterate(grid) == DijkstraState::finishFound) {
        state = BoardState::idle;
        dijkstra->drawPath();
    }
}

void Board::clearObstacles() {
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            if (gridPiece->getGridPieceState() == GridPieceState::obstacle)
                gridPiece->setGridPieceState(GridPieceState::unVisited);
}

void Board::clearVisited() {
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            if (gridPiece->getGridPieceState() == GridPieceState::visited || gridPiece->getGridPieceState() == GridPieceState::path)
                gridPiece->setGridPieceState(GridPieceState::unVisited);
}

void Board::clearBoard() {
    clearObstacles();
    clearVisited();
}

void Board::randomObstacles() {
    clearObstacles();
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            if (gridPiece->getGridPieceState() == GridPieceState::unVisited && nextRand() >= RAND_PROB)
                gridPiece->setGridPieceState(GridPieceState::obstacle);
}

void Board::resetBoard() {
    clearObstacles();
    grid[startLocation.x][startLocation.y]->setGridPieceState(GridPieceState::unVisited);
    grid[initStartLocation.x][initStartLocation.y]->setGridPieceState(GridPieceState::start);
    startLocation = initStartLocation;

    grid[finishLocation.x][finishLocation.y]->setGridPieceState(GridPieceState::unVisited);
    grid[initFinishLocation.x][initFinishLocation.y]->setGridPieceState(GridPieceState::finish);
    finishLocation = initFinishLocation;
}

void Board::recursiveMaze() {
    clearObstacles();

    // TODO: Make work.
    //recursiveBacktracker();

    GridPieceState s = GridPieceState::start, f = GridPieceState::finish;

    // Obstacle walls
    for (int x = 0; x < GRID_WIDTH; x++) {
        if (grid[x][0]->getGridPieceState() != s && grid[x][0]->getGridPieceState() != f)
            grid[x][0]->setGridPieceState(GridPieceState::obstacle);

        if (grid[x][GRID_HEIGHT - 1]->getGridPieceState() != s && grid[x][GRID_HEIGHT - 1]->getGridPieceState() != f)
            grid[x][GRID_HEIGHT - 1]->setGridPieceState(GridPieceState::obstacle);
    }

    for (int y = 0; y < GRID_HEIGHT; y++) {
        if (grid[0][y]->getGridPieceState() != s && grid[0][y]->getGridPieceState() != f)
            grid[0][y]->setGridPieceState(GridPieceState::obstacle);

        if (grid[GRID_WIDTH - 1][y]->getGridPieceState() != s && grid[GRID_WIDTH - 1][y]->getGridPieceState() != f)
            grid[GRID_WIDTH - 1][y]->setGridPieceState(GridPieceState::obstacle);
    }
}

void Board::recursiveBacktracker() {
    std::stack<GridPiece*> stack;
    stack.push(grid[1][1]);

    GridPieceState reg = GridPieceState::unVisited, obs = GridPieceState::obstacle;

    std::vector<glm::vec2> directions {
        glm::vec2(0,  1), // Up
        glm::vec2(0, -1), // Down
        glm::vec2(-1, 0), // Left
        glm::vec2(1,  0)  // Right
    };

    std::shuffle(directions.begin(), directions.end(), std::default_random_engine{});

    while (!stack.empty()) {
        GridPiece* currentCell = stack.top();
        stack.pop();

        for (const auto& d : directions) {
            glm::vec2 neighborDir = glm::vec2(currentCell->getBoardLocation().x + d.x, currentCell->getBoardLocation().y + d.y);

            // If potential neighbor is within bounds of the grid.
            if (neighborDir.x >= 0 && neighborDir.y >= 0 && neighborDir.x < GRID_WIDTH && neighborDir.y < GRID_HEIGHT) {
                if (neighborDir.x * 2 >= 0 && neighborDir.y * 2 >= 0 && neighborDir.x * 2 < GRID_WIDTH && neighborDir.y * 2 < GRID_HEIGHT) {
                    // If potential neighbor is not visited and the GridPiece one more unit away is also regular.
                    if (grid[neighborDir.x][neighborDir.y]->getGridPieceState() == reg && grid[neighborDir.x * 2][neighborDir.y * 2]->getGridPieceState() == reg) {
                        stack.push(currentCell);

                        grid[neighborDir.x][neighborDir.y]->setGridPieceState(GridPieceState::obstacle);
                        stack.push(grid[neighborDir.x][neighborDir.y]);
                        draw();
                    }
                }
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
