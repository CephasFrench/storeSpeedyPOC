#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;
class Edge
{
	public:
		Edge(string destination, pair<double, vector<pair<int, int>>> edges): destination(destination), edges(edges) {}
		Edge(pair<double, vector<pair<int, int>>> edges) : destination("NOTSET"), edges(edges) {}
		Edge(string destination, double distance) : destination(destination) {
			edges.first = distance;
		}
		// Get the name of the destination node
		string getDestination() const {
			return destination;
		}

		// Get the total distance from the source to the destination
		double getDistance() const {
			return edges.first;
		}

		// Get the path from the source to the destination
		vector<pair<int,int>> getPath() const {
			return edges.second;
		}

		string printEdge() {
			stringstream ss;
			ss << "Destination: " << destination << " Distance: " << std::setprecision(2) << edges.first << " Path: ";
			for (auto path : edges.second) {
				ss << path.first << " " << path.second << " ";
			}
			return ss.str();
		}

		string printPath()
			{
			stringstream ss;
			for (auto path : edges.second) {
				ss << path.first << " " << path.second << endl;
			}
			return ss.str();
		}

		void setDestination(string destination) {
			this->destination = destination;
		}

private:
	// Name of the node that this edge connects to
	string destination;
	// This is the total distance from the source to the destination and the path
	pair<double,vector<pair<int,int>>> edges;
};

