#ifndef NODE_FACTORY_H
#define NODE_FACTORY_H

#include <vector>
#include <utility> // Include the utility header for std::pair
#include "Node.h"

struct NodeFactory {
    int id;
    std::string name;
    std::vector<std::pair<string, double>> edges; // Use std::pair<Node, int> instead of Edge
    std::vector<std::string> items; // New vector of strings called items

    NodeFactory() {
        this->id = 0;
    }

    GraphNode createNode(std::string name, std::vector<std::pair<string, double>> edges, std::vector<std::string> items) {
        this->name = name;
        this->edges = edges;
        this->items = items;
        GraphNode node(id, edges, name, items);
        id++;
        return node; 
    }

    GraphNode createNode(std::string name, std::vector<std::pair<string, double>> edges) {
        this->name = name;
        this->edges = edges;
        GraphNode node(id, edges, name);
        id++;
        return node;
    }

};

#endif // NODE_FACTORY_H