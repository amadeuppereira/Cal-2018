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
	unsigned long long id;

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
	fNodes.close();

	ifstream fConnections;
	fConnections.open(connectionsFile);
	if (!fConnections) {
		cerr << "Unable to open file " << connectionsFile << endl;
		exit(1);
	}

	unsigned long long node1_id, node2_id;
	vector<Link> links;

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
		links.push_back(Link(id, node1_id, node2_id));

	}
	fConnections.close();


	ifstream fEdges;
	fEdges.open(edgesFile);
	if(!fEdges) {
		cerr << "Unable to open file " << edgesFile << endl;
		exit(1);
	}

	string name;
	bool two_ways;
	bool blocked = false;

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

		for(unsigned int i = 0; i < links.size(); i++) {
			if(links.at(i).edgeID == id) {
				int w = graph.calculateDist(links.at(i).nodeID1, links.at(i).nodeID2);

				graph.addEdge(links.at(i).nodeID1, links.at(i).nodeID2, w, two_ways, name, id, blocked);
				if(two_ways) {
					graph.addEdge(links.at(i).nodeID2, links.at(i).nodeID1, w, two_ways, name, id, blocked);
				}
			}
		}
	}
	fEdges.close();

}

void RoadNetwork::convertToGV() {

	gv = new GraphViewer(GV_WIDTH, GV_HEIGHT, false);
	gv->setBackground("viseu.png");
	gv->createWindow(GV_WIDTH, GV_WIDTH);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	LimitCoords l = getLimitCoords(graph);

	vector<Vertex<unsigned long long> *> vertexes = graph.getVertexSet();
	for (int i = 0; i < graph.getNumVertex(); i++) {


		int y = resizeLong(vertexes[i]->getLongitude(), l, GV_HEIGHT);
		int x = resizeLat(vertexes[i]->getLatitude(), l, GV_WIDTH);


		gv->addNode(i, x, y);
		gv->setVertexSize(i, 10);
		if (vertexes[i]->getName() != "")	// if it has a name
				{
			ostringstream label;
			label << i << " - " << vertexes[i]->getName();
			gv->setVertexLabel(i, label.str());
		}
	}

	int srcNode, dstNode;
	for (int i = 0; i < graph.getNumVertex(); i++) {
		vector<Edge<unsigned long long> > adjEdges = vertexes[i]->getAdj();
		for (unsigned int j = 0; j < adjEdges.size(); j++) {
			srcNode = graph.getIndex(vertexes[i]->getInfo());
			dstNode = graph.getIndex(adjEdges[j].getDest()->getInfo());
			if (adjEdges[j].getTwoWays())
				gv->addEdge(adjEdges[j].getId(), srcNode, dstNode,
						EdgeType::UNDIRECTED);
			else
				gv->addEdge(adjEdges[j].getId(), srcNode, dstNode,
						EdgeType::DIRECTED);

			gv->setEdgeWeight(adjEdges[j].getId(), adjEdges[j].getWeight());

			gv->setEdgeLabel(adjEdges[j].getId(), adjEdges[j].getName());
			if (adjEdges[j].getBlocked()) {
				gv->setEdgeColor(adjEdges[j].getId(), "red");
				gv->setEdgeThickness(adjEdges[j].getId(), 10);
			}
		}
	}


	gv->rearrange();

}
