#pragma once
#include <string>
#include <vector>

using namespace std;

class GraphNode {
public:
    GraphNode(int ID, vector<pair<string,double>> edges, string name, vector<string> items) : ID(ID), edges(edges), name(name), items(items) {}
    GraphNode() {}
    vector<pair<string,double>> getNeighbors() {
        return this->edges;
    }
    int getID() {
        return ID;
    }
    string getName() const {
        return name;
    }
private:
    int ID;
    string name;
    vector<pair<string,double>> edges;
    vector<string> items;
};