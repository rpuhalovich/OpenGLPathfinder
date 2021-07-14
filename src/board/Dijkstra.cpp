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

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Pseudocode
/**
 *   1  function Dijkstra(Graph, source):
 *   2
 *   3      create vertex set Q
 *   4
 *   5      for each vertex v in Graph:
 *   6          dist[v] ← INFINITY
 *   7          prev[v] ← UNDEFINED
 *   8          add v to Q
 *   9      dist[source] ← 0
 *  10
 *  11      while Q is not empty:
 *  12          u ← vertex in Q with min dist[u]
 *  13
 *  14          remove u from Q
 *  15
 *  16          for each neighbor v of u:           // only v that are still in Q
 *  17              alt ← dist[u] + length(u, v)
 *  18              if alt < dist[v]:
 *  19                  dist[v] ← alt
 *  20                  prev[v] ← u
 *  21
 *  22      return dist[], prev[]
 */

bool Dijkstra::iterate(std::vector<std::vector<GridPiece*>>& grid) {
    if (!unVisited.empty()) {
        GridPiece* min = getSmallestDistanceFromStart();
        for (const auto& d : directions) {
            // Get neighbor vec2 location.
            glm::vec2 dir = d + min->getBoardLocation();
            if (!(dir.x >= 0 && dir.y >= 0 && dir.x < 51 && dir.y < 28)) continue; // TODO: remove magic numbers.

            GridPiece* neighbor = grid[dir.x][dir.y];
            if (neighbor->getGridPieceState() == GridPieceState::start || 
                neighbor->getGridPieceState() == GridPieceState::obstacle || 
                neighbor->getGridPieceState() == GridPieceState::visited)
                continue;
            if (neighbor->getGridPieceState() == GridPieceState::finish) {
                neighbor->setPrev(min);
                finish = neighbor;
                return false;
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
    }
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
