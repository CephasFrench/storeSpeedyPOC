#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Edge.h"

using namespace std;

class GraphNode {
public:
    GraphNode(int ID, vector<Edge> edges, string name, vector<string> items) : ID(ID), edges(edges), name(name), items(items) {}
    GraphNode(int ID, vector<Edge> edges, string name) : ID(ID), edges(edges), name(name){}
    GraphNode() {};
    vector<Edge> getNeighbors() {
        return this->edges;
    }
    int getID() {
        return ID;
    }
    string getName() const {
        return name;
    }
    void addItems(string item) {
		items.push_back(item);
	}

    std::string printNameAndEdges() {
        std::stringstream ss;

        // Print name
        ss << "node " << name << std::endl;

        // Loop through and print the items
        for (const auto& item : items) {
            ss << item << std::endl;
        }

        // Print edges
        for (const auto& edge : edges) {
            ss << "aisles " << edge.getDestination() << " " << edge.getDistance() << std::endl;
            for (const auto& path : edge.getPath()) 
            {
				ss << path.first << " " << path.second << endl;
			}
        }

        return ss.str();
    }


private:
    int ID;
    string name;
    vector<Edge> edges;
    vector<string> items;
};