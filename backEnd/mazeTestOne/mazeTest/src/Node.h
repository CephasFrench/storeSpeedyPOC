#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class GraphNode {
public:
    GraphNode(int ID, vector<pair<string,double>> edges, string name, vector<string> items) : ID(ID), edges(edges), name(name), items(items) {}
    GraphNode(int ID, vector<pair<string, double>> edges, string name) : ID(ID), edges(edges), name(name){}
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
            ss << "aisles " << edge.first << " " << edge.second << std::endl;
        }

        return ss.str();
    }


private:
    int ID;
    string name;
    vector<pair<string,double>> edges;
    vector<string> items;
};