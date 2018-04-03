#ifndef SRC_ROADNETWORK_H_
#define SRC_ROADNETWORK_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Graph.h"
#include "graphviewer.h"
#include "Utils.h"
#include <set>

#define DEFAULT_VERTEX_COLOR "blue"
#define DEFAULT_EDGE_COLOR "black"
#define HIGHLIGHTED_VERTEX_COLOR "yellow"
#define HIGHLIGHTED_EDGE_COLOR "yellow"
#define BLOCKED_EDGE_COLOR "red"


class RoadNetwork {
private:
	Graph<int> graph;
	GraphViewer *gv;

public:
	RoadNetwork();
	virtual ~RoadNetwork();

	void readOSM();
	void convertToGV();


	const Graph<int>& getGraph() const;

	bool getEdgeBlockedStatus(string name);
	void setEdgeBlocked(string edge_name, bool blocked);
	double getWeightOfPath(int nodeStartID, int nodeDestinationID);
	bool printPath(int nodeStartID, int nodeDestinationID);

	void highlightNode(int id) const;
	void highlightEdge(int id) const;
	void removeHighlightNode(int id) const;
	void removeHighlightEdge(int id) const;
	//void highlightPath(vector<Vertex<int>* > p) const;
	void blockEdge(int id) const;
	void removeBlockEdge(int id) const;

	void updateMap() const;
};





#endif /* SRC_ROADNETWORK_H_ */

