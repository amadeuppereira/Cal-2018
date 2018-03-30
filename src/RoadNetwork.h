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


class RoadNetwork {
private:
	Graph<unsigned long long> graph;
	GraphViewer *gv;
	int sourceID;
	int destinyID;


public:
	RoadNetwork();
	virtual ~RoadNetwork();

	int getDestinyId() const;
	void setDestinyId(int destinyId);
	int getSourceId() const;
	void setSourceId(int sourceId);
	void readOSM();
	void convertToGV();
};





#endif /* SRC_ROADNETWORK_H_ */

