#pragma once
#include "Node.h"
#include <list>
#include <utility>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream> // Add this line to include the <sstream> header

using namespace std;

class Maze {
public:
    Maze(const std::string& file) : fileName(file) {
        fileParser();
    }
    vector<vector<string>> mazeArray;
    
private:
    std::list<std::pair<GraphNode,double>> nodeDistanceList;
    std::string fileName;
    
    void fileParser();

};