#include <iostream>
#include <fstream>
#include <string>
#include "Maze.h"

using namespace std;

int main() {
    Maze maze("testMaze.txt");

    // loop through and print maze array
    for (auto row : maze.mazeArray) {
        for (auto col : row) {
            std::cout << col << "-";
        }
        std::cout << std::endl;
    }

    return 0;
}