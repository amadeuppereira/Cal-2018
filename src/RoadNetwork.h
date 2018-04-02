#ifndef SRC_ROADNETWORK_H_
#define SRC_ROADNETWORK_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Graph.h"
#include "graphviewer.h"
#include "Utils.h"
#include <set>


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
	vector<string> getNodesPathVector(int nodeStartID, int nodeDestinationID);
	vector<string> getEdgesPathVector(int nodeStartID, int nodeDestinationID);
};





#endif /* SRC_ROADNETWORK_H_ */

