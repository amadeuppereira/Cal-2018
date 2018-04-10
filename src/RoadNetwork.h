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
#define DEFAULT_EDGE_COLOR "green"
#define HIGHLIGHTED_VERTEX_COLOR "yellow"
#define HIGHLIGHTED_EDGE_COLOR "yellow"
#define MEDIUM_TRAFFIC "orange"
#define HIGH_TRAFFIC "red"
#define BLOCKED_EDGE_COLOR "black"


class RoadNetwork {
private:
	Graph<int> graph;
	GraphViewer *gv;
public:
	RoadNetwork();
	virtual ~RoadNetwork();
	void readOSM();
	void writeEdgeFile();
	void convertToGV();
	const Graph<int>& getGraph() const;
	bool getEdgeBlockedStatus(string name);
	void setEdgeBlocked(string edge_name, bool blocked);
	double getWeightOfPath(vector<Vertex<int>*> vec);
	void printPath(int nodeStartID, int nodeDestinationID);
	void printAllCarPath() const;
	void printCarID() const;
	void removeCar(int id);
	void writeCarsFile();
	void highlightNode(int id) const;
	void highlightEdge(int id) const;
	void removeHighlightNode(int id) const;
	void removeHighlightEdge(int id) const;
	void blockEdge(int id) const;
	void removeBlockEdge(int id) const;
	void updateMap() const;
	void closeMapWindow() const;
	void updateInfo();
};





#endif /* SRC_ROADNETWORK_H_ */

