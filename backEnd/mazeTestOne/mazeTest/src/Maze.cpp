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
// The goal of this function is to make it so that the nodeNameDistanceList is populated with the nodes
// NOTE: This function does not store the distance of the nodes, only the name
void Maze::storeNodes()
{
    // loop though the 2d vector
    // for each element that is not a 1 or a 0, create a node
    // add a counter of row and column to the node
    int rowCounter = 0;
    for (auto row : mazeArray)
	{
        int columnCounter = 0;
		for (string element : row)
		{
			if (element != "1" && element != "0")
			{
                this->nodeNameAndLocation.push_back(make_pair(element, make_pair(rowCounter,columnCounter)));
			}
            columnCounter++;
		}
        rowCounter++;
	}
}
