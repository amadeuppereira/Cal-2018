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
	Graph<unsigned long long> graph;
	GraphViewer *gv;

public:
	RoadNetwork();
	virtual ~RoadNetwork();

	void readOSM();
	void convertToGV();

	const Graph<unsigned long long>& getGraph() const;

	bool getEdgeBlockedStatus(string name);
	void setEdgeBlocked(string edge_name, bool blocked);
	double getWeightOfPath(unsigned long long nodeStartID, unsigned long long nodeDestinationID);
};





#endif /* SRC_ROADNETWORK_H_ */

