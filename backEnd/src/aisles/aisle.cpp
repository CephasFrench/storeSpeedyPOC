#include "aisle.h"

const std::vector<Aisle>& Aisle::getNeighbors() const {
    return neighbors;
}

void Aisle::addNeighbor(const Aisle& neighbor) {
    neighbors.push_back(neighbor);
}
