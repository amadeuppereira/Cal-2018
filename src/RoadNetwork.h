#ifndef SRC_ROADNETWORK_H_
#define SRC_ROADNETWORK_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Graph.h"

#define W_WIDTH 600;
#define W_HEIGHT 600;

class RoadNetwork {
private:
	Graph<unsigned> graph;
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
};








#endif /* SRC_ROADNETWORK_H_ */

