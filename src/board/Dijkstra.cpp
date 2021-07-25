#include "Dijkstra.hpp"

Dijkstra::Dijkstra(glm::vec2 gridDimensions) :
    finish(nullptr), gridDimensions(gridDimensions)
{
}

Dijkstra::~Dijkstra() {

}

void Dijkstra::init(std::vector<std::vector<GridPiece*>>& grid) {
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            gridPiece->init();

    unVisited = getGridVector(grid);
}

DijkstraState Dijkstra::iterate(std::vector<std::vector<GridPiece*>>& grid) {
    if (!unVisited.empty()) {

        GridPiece* min = getSmallestDistanceFromStart();
        if (min->getDistanceFromStart() == INT_MAX)
            return DijkstraState::finishNotFound;

        for (const auto& d : directions) {
            // Get neighbor vec2 location.
            glm::vec2 dir = d + min->getBoardLocation();
            // If this potential neighbor is outside of board dimensions, continue.
            if (!(dir.x >= 0 && dir.y >= 0 && dir.x < gridDimensions.x && dir.y < gridDimensions.y))
                continue;

            GridPiece* neighbor = grid[dir.x][dir.y];
            if (neighbor->getGridPieceState() == GridPieceState::start || 
                neighbor->getGridPieceState() == GridPieceState::obstacle || 
                neighbor->getGridPieceState() == GridPieceState::visited)
                continue;
            if (neighbor->getGridPieceState() == GridPieceState::finish) {
                neighbor->setPrev(min);
                finish = neighbor;
                return DijkstraState::finishFound;
            }

            neighbor->setGridPieceState(GridPieceState::visiting);

            // Calc distance to start from node
            neighbor->setPrev(min);
            int calcDist = calcDistance(neighbor);
            if (neighbor->getDistanceFromStart() > calcDist) {
                neighbor->setDistanceFromStart(calcDist);
            }

            neighbor->setGridPieceState(GridPieceState::visited);
            visited.push_back(neighbor);
        }
        return DijkstraState::running;
    }
    return DijkstraState::finishNotFound;
}

void Dijkstra::drawPath() {
    GridPiece* temp = finish;
    while (temp->getPrev() != nullptr) {
        temp = temp->getPrev();
        if (temp->getGridPieceState() != GridPieceState::start) temp->setGridPieceState(GridPieceState::path);
    }
}

std::vector<GridPiece*> Dijkstra::getGridVector(const std::vector<std::vector<GridPiece*>>& grid) {
    std::vector<GridPiece*> out;
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            out.push_back(gridPiece);
    return out;
}

GridPiece* Dijkstra::getSmallestDistanceFromStart() {
    GridPiece* min = unVisited[0];

    for (int i = 0; i < unVisited.size(); i++) {
        if (unVisited[i]->getDistanceFromStart() < min->getDistanceFromStart()) {
            min = unVisited[i];
        }
    }

    unVisited.erase(std::remove(unVisited.begin(), unVisited.end(), min), unVisited.end());
    return min;
}

int Dijkstra::calcDistance(GridPiece* gp) {
    int count = 0;
    GridPiece* temp = gp;
    while (temp->getPrev() != nullptr) {
        temp = temp->getPrev();
        count++;
    }
    return count;
}
