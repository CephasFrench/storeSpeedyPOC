#include <list>
#include "Node.h"


class Path {
private:
    std::vector<GraphNode> nodes;
    double totalLength;

public:
    // Constructor
    Path() : totalLength(0.0) {}

    // Add a node to the path
    void addNode(const GraphNode& node, double length) {
        nodes.push_back(node);
        totalLength += length;
    }

    // Get the nodes in the path
    std::vector<GraphNode> getNodes() const {
        return nodes;
    }

    // Get the total length of the path
    double getTotalLength() const {
        return totalLength;
    }

    // size of the path
    int size() const {
		return nodes.size();
	}
};