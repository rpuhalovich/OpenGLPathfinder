#include "Dijkstra.hpp"

void Dijkstra::init(Board* b) {
    for (auto const& gridCol : b->getGrid())
        for (auto const& gridPiece : gridCol)
            gridPiece->initDistanceFromStart();
}

void Dijkstra::iterate(Board* b) {

}
