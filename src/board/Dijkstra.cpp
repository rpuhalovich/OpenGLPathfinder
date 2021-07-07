#include "Dijkstra.hpp"

void Dijkstra::init(std::vector<std::vector<GridPiece*>> grid) {
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            gridPiece->initDistanceFromStart();
    unVisited = getGridVector(grid);
}

bool Dijkstra::iterate(std::vector<std::vector<GridPiece*>> grid) {
    if (!unVisited.empty()) {
        GridPiece* min = getSmallestDistanceFromStart(unVisited);
        for (const auto& d : directions) {
            // Get neighbor vec2 location.
            glm::vec2 dir = d + min->getBoardLocation();
            if (glm::all(glm::greaterThanEqual(dir, glm::vec2(0, 0)))) continue; // If location off grid then skip.
            GridPiece* neighbor = grid[dir.x][dir.y];
            neighbor->setGridPieceState(GridPieceState::visiting);

            // Calc distance to start from node
            int calcDist = calcDistance(neighbor);
            if (neighbor->getDistanceFromStart() > calcDist) {
                neighbor->setDistanceFromStart(calcDist);
                neighbor->setPrev(min);
            }

            neighbor->setGridPieceState(GridPieceState::visited);
            visited.push_back(neighbor);
            if (neighbor->getGridPieceState() == GridPieceState::finish) return false;
        }
    }
}

std::vector<GridPiece*> Dijkstra::getGridVector(std::vector<std::vector<GridPiece*>> grid) {
    std::vector<GridPiece*> out;
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            out.push_back(gridPiece);
    return out;
}

GridPiece* Dijkstra::getSmallestDistanceFromStart(std::vector<GridPiece*> unVisited) {
    GridPiece* min;
    for (int i = 0; i < unVisited.size(); i++) {
        if (unVisited[i]->getDistanceFromStart() < min->getDistanceFromStart()) min = unVisited[i];
        unVisited.erase(unVisited.begin() + i);
    }
    return min;
}

int Dijkstra::calcDistance(GridPiece* gp) {
    int count = 0;
    GridPiece* temp = gp;
    while (gp->getPrev() != nullptr) {
        temp = temp->getPrev();
        count++;
    }
    return count;
}
