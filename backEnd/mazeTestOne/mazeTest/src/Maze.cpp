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

bool Maze::isValid(int row, int col)
{
    return row >= 0 && col >= 0 && row < this->mazeArray.size() && col < this->mazeArray[0].size() && this->mazeArray[row][col] != "0";
}

int Maze::dijkstra(pair<int, int> start, pair<int, int> end)
{
    // Create a priority queue to store the nodes to be visited
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    // Create a 2D vector to store the distances from the start node
    vector<vector<int>> distance(mazeArray.size(), vector<int>(mazeArray[0].size(), INT_MAX));

    // Set the distance of the start node to 0
    distance[start.first][start.second] = 0;

    // Push the start node into the priority queue
    pq.push(make_pair(0, start));

    // Create a vector to store the visited nodes
    vector<vector<bool>> visited(mazeArray.size(), vector<bool>(mazeArray[0].size(), false));

    // Loop until the priority queue is empty
    while (!pq.empty())
    {
        // Get the current node from the priority queue
        pair<int, pair<int, int>> current = pq.top();
        pq.pop();

        // Get the coordinates of the current node
        int row = current.second.first;
        int col = current.second.second;

        // Check if the current node is the end node
        if (current.second == end)
        {
            // Return the distance to the end node
            return distance[row][col];
        }

        // Check if the current node has already been visited
        if (visited[row][col])
        {
            continue;
        }

        // Mark the current node as visited
        visited[row][col] = true;

        // Get the neighbors of the current node
        vector<pair<int, int>> neighbors = {
            {row - 1, col}, // Up
            {row + 1, col}, // Down
            {row, col - 1}, // Left
            {row, col + 1}  // Right
        };

        // Loop through the neighbors
        for (const auto& neighbor : neighbors)
        {
            int neighborRow = neighbor.first;
            int neighborCol = neighbor.second;

            // Check if the neighbor is valid and not visited
            if (isValid(neighborRow, neighborCol) && !visited[neighborRow][neighborCol])
            {
                // Calculate the distance to the neighbor
                int neighborDistance = distance[row][col] + 1;

                // Update the distance if it is shorter
                if (neighborDistance < distance[neighborRow][neighborCol])
                {
                    distance[neighborRow][neighborCol] = neighborDistance;
                    pq.push(make_pair(neighborDistance, make_pair(neighborRow, neighborCol)));
                }
            }
        }
    }

    // If the end node is not reachable, return -1
    return -1;
}
