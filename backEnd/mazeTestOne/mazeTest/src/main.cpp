#include <iostream>
#include <fstream>
#include <string>
#include "Maze.h"

using namespace std;

int main() {

    Maze maze("testMaze.txt");
    list<GraphNode> nodes = maze.getNodes();
    for (auto node : nodes) {
		node.printNameAndEdges();
	}

    return 0;
}