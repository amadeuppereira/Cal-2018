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

	string line;
	unsigned long int id;

	ifstream fNodes;
	fNodes.open(nodesFile);
	if(!fNodes) {
		cerr << "Unable to open file " << nodesFile << endl;
		exit(1);
	}
	long double latitude, longitude;

	while (getline(fNodes, line)) {
		string data;
		istringstream linestream(line);

		getline(linestream, data, ';');
		id = atof(data.c_str());
		getline(linestream, data, ';');
		latitude = atof(data.c_str());
		getline(linestream, data, ';');
		longitude = atof(data.c_str());

		//cout << "node_id:" << id << ", lat: " << latitude << ", long: " << longitude << endl;
		graph.addVertex(id,latitude,longitude);
	}


	ifstream fEdges;
	fEdges.open(edgesFile);
	if(!fEdges) {
		cerr << "Unable to open file " << edgesFile << endl;
		exit(1);
	}

	string name;
	bool two_ways;

	while (getline(fEdges, line)) {
		string data;
		istringstream linestream(line);

		getline(linestream, data, ';');
		id = atof(data.c_str());
		getline(linestream, data, ';');
		name = data;
		getline(linestream, data, ';');
		if(data == "True")
			two_ways = true;
		else
			two_ways = false;

		//cout << "road_id:" << id << ", name: " << name << ", two_ways: " << two_ways << endl;
		name = "";
	}

	ifstream fConnections;
	fConnections.open(connectionsFile);
	if(!fConnections) {
		cerr << "Unable to open file " << connectionsFile << endl;
		exit(1);
	}

	unsigned long int node1_id, node2_id;

	while (getline(fConnections, line)) {
		string data;
		istringstream linestream(line);

		getline(linestream, data, ';');
		id = atof(data.c_str());
		getline(linestream, data, ';');
		node1_id = atof(data.c_str());
		getline(linestream, data, ';');
		node2_id = atof(data.c_str());


		//cout << "road_id:" << id << ", node1_id: " << node1_id << ", node2_id: " << node2_id << endl;
	}

}
