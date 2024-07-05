#include "Maze.h"
// Add this line to include the <sstream> header

using namespace std;

void Maze::fileParser() {
    // Open the file and check to see if it is open
    ifstream file(fileName);
    try {
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        // Your file processing code here

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return;
    }
    // Now that the file is open, we can read the contents
    string line;
    while (getline(file, line)) {
        // Store each line in a string stream
        stringstream ss(line);
        // Create a vector to store the values in the line
        vector<string> lineVector;
        while (ss >> line)
        {
            lineVector.push_back(line);
        }
        // Add the line vector to the maze array
        mazeArray.push_back(lineVector);
    }
}