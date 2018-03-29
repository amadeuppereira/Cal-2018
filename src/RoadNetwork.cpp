#include "RoadNetwork.h"

RoadNetwork::RoadNetwork() {
	// TODO Auto-generated constructor stub

}

RoadNetwork::~RoadNetwork() {
	// TODO Auto-generated destructor stub
}

int RoadNetwork::getDestinyId() const {
	return destinyID;
}

void RoadNetwork::setDestinyId(int destinyId) {
	destinyID = destinyId;
}

int RoadNetwork::getSourceId() const {
	return sourceID;
}

void RoadNetwork::setSourceId(int sourceId) {
	sourceID = sourceId;
}

void RoadNetwork::readOSM() {
	string nodesFile = "nodes.txt";
	string edgesFile = "edges.txt";
	string connectionsFile = "connections.txt";

	ifstream fNodes;
	fNodes.open(nodesFile);
	if(!fNodes) {
		cerr << "Unable to open file " << nodesFile << endl;
		exit(1);
	}
	string line;
	unsigned id;
	double latitude, longitude;

	while (getline(fNodes, line)) {
		string data;
		istringstream linestream(line);

		getline(linestream, data, ';');
		id = atoi(data.c_str());
		getline(linestream, data, ';');
		latitude = atof(data.c_str());
		getline(linestream, data, ';');
		longitude = atof(data.c_str());

		cout << "id:" << id << ", lat: " << latitude << ", long: " << longitude << endl;
	}
}
