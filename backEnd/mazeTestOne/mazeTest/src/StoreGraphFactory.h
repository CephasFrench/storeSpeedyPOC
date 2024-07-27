#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "StoreGraph.h"
#include "NodeFactory.h"
using namespace std;
class StoreGraphFactory {
public:
    // TODO: Add function declarations here
    StoreGraph getGraph(const std::string& fileName)
    {
        // parse file here

            // Open the file
            std::ifstream file(fileName);

            // Check if the file is open
            if (!file.is_open()) {
                // Handle the error, e.g., throw an exception or return an error code
                throw std::runtime_error("Failed to open file");
            }

            // Create a vector to store the nodes
            std::vector<GraphNode> nodes;

            // Read the file word by word
            std::string word;
            file >> word;
            NodeFactory nodeFactory;
            while (true) {
                // Process each word of the file
                // TODO: Implement your logic here
                if(word == "node")
                {
                    // Get name
                    string name;
                    file >> name;
                    // loop though and get all the items
                    vector<string> items;
                    while(file >> word)
                    {
                        if(word == "aisles")
                        {
                            break;
                        }
                        items.push_back(word);
                    }
                    // loop though and get all the aisles
                    vector<Edge> edges;
                    while(true)
                    {
                        if(word == "node" || word == "exit")
                        {
                            break;
                        }

                        //string aisle = word;
                        string aisle;
                        file >> aisle;
                        double distance;
                        file >> distance;
                        //edges.push_back(make_pair(aisle, distance));
                        edges.push_back(Edge(aisle, distance));
                        file >> word;
                    }
                    // Now have all the data to create a node
                    GraphNode node = nodeFactory.createNode(name, edges, items);
                    // Add node to vector
                    nodes.push_back(node);
                }
                else if(word == "exit")
                {
                    break;
                }
                else
                {
                    // Handle the error, e.g., throw an exception or return an error code
                    throw std::runtime_error("Invalid file format");
                }
            }
            // Close the file
            file.close();

            // DONE: Send data to NodeFactory to create nodes - this is done in the input loop

            // TODO: Create a StoreGraph object with the nodes in a vector
            StoreGraph storeGraph(nodes);

            // TODO: Return the StoreGraph object
            return storeGraph;
    }
    StoreGraph getGraph(stringstream input)
    {
        // Create a vector to store the nodes
        std::vector<GraphNode> nodes;

        // Read the file word by word
        std::string word;
        input >> word;
        NodeFactory nodeFactory;
        while (true) {
            // Process each word of the file
            // TODO: Implement your logic here
            if (word == "node")
            {
                // Get name
                string name;
                input >> name;
                // loop though and get all the items
                vector<string> items;
                while (input >> word)
                {
                    if (word == "aisles")
                    {
                        break;
                    }
                    items.push_back(word);
                }
                // loop though and get all the aisles
                vector<Edge> edges;
                while (true)
                {
                    if (word == "node" || word == "exit")// std::all_of(word.begin(), word.end(), ::isdigit))
                    {
                        break;
                    }

                    //string aisle = word;
                    string aisle;
                    input >> aisle;
                    int distance;
                    input >> distance;
                    // Now we known that the next word is a cordinate
                    vector<pair<int, int>> cordinates;
                    input >> word;
                    while (word != "aisles" and word != "node" and word != "exit")
                    {
                        pair<int, int> cordinate;
                        cordinate.first = stoi(word);
                        input >> word;
                        cordinate.second = stoi(word);
                        cordinates.push_back(cordinate);
                        input >> word;
                    }

                    //edges.push_back(make_pair(aisle, distance));
                    edges.push_back(Edge(aisle, make_pair(distance, cordinates)));
                    //input >> word;
                }
                // Now have all the data to create a node
                GraphNode node = nodeFactory.createNode(name, edges, items);
                // Add node to vector
                nodes.push_back(node);

            }
            else if (word == "exit")
            {
                break;
            }
            else
            {
                // Handle the error, e.g., throw an exception or return an error code
                throw std::runtime_error("Invalid sstream format");
            }
        }
        // DONE: Send data to NodeFactory to create nodes - this is done in the input loop

        // TODO: Create a StoreGraph object with the nodes in a vector
        StoreGraph storeGraph(nodes);

        // TODO: Return the StoreGraph object
        return storeGraph;
    }

private:
    // TODO: Add private member variables here
};