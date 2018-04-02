#include "RoadNetwork.h"



RoadNetwork::RoadNetwork() {
	// TODO Auto-generated constructor stub

}

RoadNetwork::~RoadNetwork() {
	// TODO Auto-generated destructor stub
}

void RoadNetwork::readOSM() {
	string nodesFile = "nodes.txt";
	string edgesFile = "edges.txt";
	string connectionsFile = "connections.txt";

	string line;
	int id;
	string name;

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
		name = data;
		getline(linestream, data, ';');
		latitude = atof(data.c_str());
		getline(linestream, data, ';');
		longitude = atof(data.c_str());

		graph.addVertex(id,name,latitude,longitude);
	}
	fNodes.close();

	ifstream fConnections;
	fConnections.open(connectionsFile);
	if (!fConnections) {
		cerr << "Unable to open file " << connectionsFile << endl;
		exit(1);
	}

	int node1_id, node2_id;
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


		links.push_back(Link(id, node1_id, node2_id));

	}
	fConnections.close();


	ifstream fEdges;
	fEdges.open(edgesFile);
	if(!fEdges) {
		cerr << "Unable to open file " << edgesFile << endl;
		exit(1);
	}

	name = "";
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


		for(unsigned int i = 0; i < links.size(); i++) {
			if(links.at(i).edgeID == id) {
				double w = graph.calculateDist(links.at(i).nodeID1, links.at(i).nodeID2);

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
	gv->setBackground("mapa.png");
	gv->createWindow(GV_WIDTH, GV_WIDTH);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	LimitCoords l = getLimitCoords(graph);

	vector<Vertex<int> *> vertexes = graph.getVertexSet();
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
		vector<Edge<int> > adjEdges = vertexes[i]->getAdj();
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

const Graph<int>& RoadNetwork::getGraph() const {
	return graph;
}

bool RoadNetwork::getEdgeBlockedStatus(string name){
    for(size_t i  = 0; i < graph.getVertexSet().size(); i++){
    	for(size_t n = 0; n < graph.getVertexSet().at(i)->getAdj().size(); n++){
    		if(graph.getVertexSet().at(i)->getAdj().at(n).getName() != "")
    			if(graph.getVertexSet().at(i)->getAdj().at(n).getName() == name)
    				return graph.getVertexSet().at(i)->getAdj().at(n).getBlocked();
    	}
    }
    return false;
}

void RoadNetwork::setEdgeBlocked(string edge_name, bool blocked){
    for(size_t i  = 0; i < graph.getVertexSet().size(); i++){
    	for(size_t n = 0; n < graph.getVertexSet().at(i)->getAdj().size(); n++){
    		if(graph.getVertexSet().at(i)->getAdj().at(n).getName() != "")
    			if(graph.getVertexSet().at(i)->getAdj().at(n).getName() == edge_name){
    				graph.setEdgeBlocked(graph.getVertexSet().at(i)->getAdj().at(n).getId(),blocked);
    			}
    	}
    }
}

double RoadNetwork::getWeightOfPath(int nodeStartID, int nodeDestinationID) {
	double totalWeight = 0;
	graph.dijkstraShortestPath(nodeStartID);
	vector<int> graphPath = graph.getPath(nodeStartID,nodeDestinationID);
	for(size_t i = 0; i < graphPath.size(); i++){
		for(size_t n = 0; n < graph.getVertex(graphPath.at(i))->getAdj().size(); n++){
			if(i < graphPath.size() - 1)
				if(graph.getVertex(graphPath.at(i))->getAdj().at(n).getDest()->getName() == graph.getVertex(graphPath.at(i + 1))->getName())
					totalWeight += graph.getVertex(graphPath.at(i))->getAdj().at(n).getWeight();
		}
	}
	return totalWeight;
}

vector<string> RoadNetwork::getNodesPathVector(int nodeStartID, int nodeDestinationID){
	vector<string> ret;
	graph.dijkstraShortestPath(nodeStartID);
	vector<int> graphPath = graph.getPath(nodeStartID,nodeDestinationID);
	for(size_t i = 0; i < graphPath.size(); i++){
		ret.push_back(graph.getVertex(graphPath.at(i))->getName());
	}
	return ret;
}

vector<string> RoadNetwork::getEdgesPathVector(int nodeStartID, int nodeDestinationID){
	vector<string> ret;
	graph.dijkstraShortestPath(nodeStartID);
	vector<int> graphPath = graph.getPath(nodeStartID,nodeDestinationID);
	for(size_t i = 0; i < graphPath.size(); i++){
		for(size_t n = 0; n < graph.getVertex(graphPath.at(i))->getAdj().size(); n++){
			if(i < graphPath.size() - 1)
				if(graph.getVertex(graphPath.at(i))->getAdj().at(n).getDest()->getName() == graph.getVertex(graphPath.at(i + 1))->getName())
					ret.push_back(graph.getVertex(graphPath.at(i))->getAdj().at(n).getName());
		}
	}
	return ret;
}


