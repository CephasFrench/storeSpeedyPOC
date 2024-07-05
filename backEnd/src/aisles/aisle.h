#ifndef AISLE_H
#define AISLE_H

#include <vector>

class Aisle {
public:
    int num;
    const std::vector<Aisle>& getNeighbors() const;
    void addNeighbor(const Aisle& neighbor);

private:
    std::vector<Aisle> neighbors;
};

#endif // AISLE_H
