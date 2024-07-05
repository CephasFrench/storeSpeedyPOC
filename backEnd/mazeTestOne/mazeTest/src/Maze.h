#pragma once
#include "NodeFactory.h"
#include <list>
#include <utility>
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
    }
    
private:
    std::string fileName;
    vector<vector<string>> mazeArray;
    std::list<std::pair<string,pair<int,int>>> nodeNameAndLocation;
    
    void fileParser();
    void storeNodes();

};