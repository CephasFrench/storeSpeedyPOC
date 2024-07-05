#pragma once
#include "NodeFactory.h"
#include <list>
#include <utility>
#include <queue>
#include <stdexcept>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> // Add this line to include the <sstream> header

using namespace std;

class Maze {
public:
    Maze(const std::string& file) : fileName(file) {
        fileParser();
        storeNodes();
        makeNodes();
    }
    
    // TODO: MAKE THIS PRIVATE
    list<GraphNode> getNodes() {
		return Nodes;
	}

private:
    std::string fileName;
    vector<vector<string>> mazeArray;
    std::list<std::pair<string,pair<int,int>>> nodeNameAndLocation;
    list<GraphNode> Nodes;
    
    void fileParser();
    void storeNodes();
    bool isValid(int row, int col);
    int dijkstra(pair<int,int> start, pair<int,int> end);
    void makeNodes();

};