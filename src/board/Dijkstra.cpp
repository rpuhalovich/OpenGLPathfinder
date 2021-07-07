#include "Dijkstra.hpp"

Dijkstra::Dijkstra() {

}

Dijkstra::~Dijkstra() {

}

void Dijkstra::init(std::vector<std::vector<GridPiece*>>& grid) {
    for (auto const& gridCol : grid)
        for (auto const& gridPiece : gridCol)
            gridPiece->init();

    unVisited = getGridVector(grid);
}

bool Dijkstra::iterate(std::vector<std::vector<GridPiece*>>& grid) {
    if (!unVisited.empty()) {
        GridPiece* min = getSmallestDistanceFromStart();
        for (const auto& d : directions) {
            // Get neighbor vec2 location.
            glm::vec2 dir = d + min->getBoardLocation();
            
            // If location off grid then skip.
            if (glm::all(glm::lessThanEqual(dir, glm::vec2(0, 0))) || glm::all(glm::greaterThan(dir, glm::vec2(grid.size(), grid[0].size())))) 
                continue;

            GridPiece* neighbor = grid[dir.x][dir.y];
            if (neighbor->getGridPieceState() == GridPieceState::start || 
                neighbor->getGridPieceState() == GridPieceState::obstacle || 
                neighbor->getGridPieceState() == GridPieceState::visited)
                continue;
            if (neighbor->getGridPieceState() == GridPieceState::finish)
                return false;

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
            unVisited.erase(unVisited.begin() + i);
        }
    }
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
