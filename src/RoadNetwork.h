#ifndef SRC_ROADNETWORK_H_
#define SRC_ROADNETWORK_H_

#include "Graph.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"
#include <float.h>
#include <algorithm>

class RoadNetwork {
private:
	Graph<unsigned> graph;
	//GraphViewer * gv;
	int sourceID;
	int destinyID;


public:
	RoadNetwork();
	virtual ~RoadNetwork();

	int getDestinyId() const;
	void setDestinyId(int destinyId);
	int getSourceId() const;
	void setSourceId(int sourceId);
};








#endif /* SRC_ROADNETWORK_H_ */

