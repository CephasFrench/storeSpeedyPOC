#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "Maze.h"
#include "StoreGraphFactory.h"

using namespace std;

int main() {
    auto start = std::chrono::high_resolution_clock::now(); // Store the current time

    //////////////////////////////////////////////////////////
    //Maze maze("testMaze.txt");
    Maze maze("vmstoretext_readable.txt");
    StoreGraphFactory myStoreGraphFactory;
    cout << "diskstras done now making graph" << endl;
    StoreGraph myGraph = myStoreGraphFactory.getGraph(maze.getNodeData());
    Path path = myGraph.FindPath();

    //////////////////////////////////////////////////////////

    cout << "The shortest path is:" << endl;
    cout << path.size() << " nodes" << endl;
    cout << "the total distance is: " << myGraph.getTotalDistance() << endl;
    // Print the path
    for (const auto& node : path.getNodes()) {
        cout << node.getName() << endl;
    }

    auto end = std::chrono::high_resolution_clock::now(); // Store the current time
    auto duration = chrono::duration_cast<std::chrono::milliseconds>(end - start); // Calculate the duration
    int minutes = duration.count() / 60000;
    int seconds = (duration.count() % 60000) / 1000;
    int milliseconds = duration.count() % 1000;

    cout << "Execution time: " << minutes << " minutes, " << seconds << " seconds, " << milliseconds << " milliseconds" << endl;


    return 0;
}