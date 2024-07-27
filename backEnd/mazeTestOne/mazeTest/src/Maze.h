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
#include <fstream>
#include <sstream> // Add this line to include the <sstream> header

using namespace std;

class Maze {
public:
    Maze() {}
    Maze(const std::string& file)
    {
        this->fileName = file;
        fileParser();
        storeNodes();
        makeNodes();
    }


    string start(const std::string& file)
    {
        this->fileName = file;
        fileParser();
        storeNodes();
        return makeNodes();
	}
    
    stringstream getNodeData();

private:
    std::string fileName;
    vector<vector<string>> mazeArray;
    std::list<std::pair<string,pair<int,int>>> nodeNameAndLocation;
    list<GraphNode> Nodes;
    
    void fileParser();
    void storeNodes();
    bool isValid(int row, int col);
    //int dijkstra(pair<int,int> start, pair<int,int> end);
    Edge dijkstra(pair<int, int> start, pair<int, int> end);
    string makeNodes();
    list<GraphNode> getNodes() {
		return Nodes;
	}

};