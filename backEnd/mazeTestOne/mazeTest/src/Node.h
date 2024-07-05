#pragma once
#include <string>
#include <vector>
#include <iostream>

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

    void printNameAndEdges() {
		cout << "Node: " << name << endl;
		cout << "Edges: " << endl;
		for (auto edge : edges) {
			cout << "    " << edge.first << " " << edge.second << endl;
		}
	}

private:
    int ID;
    string name;
    vector<pair<string,double>> edges;
    vector<string> items;
};