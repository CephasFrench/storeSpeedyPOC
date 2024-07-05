#include <iostream>
#include <string>
#include <chrono>
#include "StoreGraphFactory.h"
using namespace std;

int main() {
    auto start = std::chrono::high_resolution_clock::now(); // Store the current time
    StoreGraphFactory storeGraphFactory;
    StoreGraph myGraph = storeGraphFactory.getGraph("list4.txt");
    std::vector<GraphNode> path = myGraph.FindPath();

    cout << "The shortest path is:" << endl;
    cout << path.size() << " nodes" << endl;
    cout << "the total distance is: " << myGraph.getTotalDistance() << endl;
    // Print the path
    for (const auto& node : path) {
        cout << node.getName() << endl;
    }

    auto end = std::chrono::high_resolution_clock::now(); // Store the current time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // Calculate the duration
    int minutes = duration.count() / 60000;
    int seconds = (duration.count() % 60000) / 1000;
    int milliseconds = duration.count() % 1000;

    cout << "Execution time: " << minutes << " minutes, " << seconds << " seconds, " << milliseconds << " milliseconds" << endl;

    return 0;
}