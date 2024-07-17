#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Node.h"
#include "Path.h"
#include <vector>
#include <string>

using namespace std;

class StoreGraph {
private:

public:
    std::vector<GraphNode> nodes;
    StoreGraph(const std::vector<GraphNode>& nodes) : nodes(nodes) {
        // Constructor implementation
        myNodes = nodes;
    }

    double getTotalDistance() {
        return shortestPath.getTotalLength();
    }

    Path FindPath() {
        Path currentPath;

        // Find the start node
        cout << "Finding the start node" << endl;
        for (int i = 0; i < myNodes.size(); i++) {
            GraphNode node = myNodes[i];
            if (node.getName() == "entrance") {
                startNode = node;
                // erase the start node from the list
                myNodes.erase(myNodes.begin() + i);
                break;
            }
        }
        
        // now have the start node find the path
        cout << "Finding the path" << endl;
        pathCall(myNodes, startNode, currentPath);

        return shortestPath;
        // TODO: Implement return here!!!
    }



private:
    vector<GraphNode> myNodes;
    Path shortestPath;
    GraphNode startNode;

    void pathCall(vector<GraphNode> nodes, GraphNode previousNode, Path currentPath)
    {
        // Base case, if there is only one nude left, add it to the path and return
        if(nodes.size() == 1)
        {
            // Get the distance from the previous node to the current node
            double distance = 0.0;
            for(auto edge : previousNode.getNeighbors())
            {
                if(edge.first == nodes[0].getName())
                {
                    distance = edge.second;
                    break;
                }
            }

            currentPath.addNode(nodes[0], distance);

            // Add distance from the last node to the entrance
            for(auto edge : nodes[0].getNeighbors())
            {
                if(edge.first == "entrance")
                {
                    currentPath.addNode(startNode, edge.second);
                    break;
                }
            }

            if(currentPath.getTotalLength() < shortestPath.getTotalLength() || shortestPath.getTotalLength() == 0)
            {
                shortestPath = currentPath;
            }
            return;
        }


        // Loop though each node and pass the list minus the current node in a recusive call
        for(int i = 0; i < nodes.size(); i++)
        {
            // temp path
            Path tempPath = currentPath;

            // Get the current node
            GraphNode currentNode = nodes[i];
            // Find the distance from the current node to the previous node
            double distance = 0;
            for(auto edge : previousNode.getNeighbors())
            {
                if(edge.first == currentNode.getName())
                {
                    distance = edge.second;
                    break;
                }
            }

            // Add the current node to the path
            tempPath.addNode(currentNode, distance);      

            // Make a coppy of the nodes and remove the current node
            vector<GraphNode> newNodes = nodes;
            newNodes.erase(newNodes.begin() + i);

            // now call the function again
            pathCall(newNodes, currentNode, tempPath);      
        }
    }


};