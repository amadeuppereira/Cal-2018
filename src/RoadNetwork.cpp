#include "RoadNetwork.h"


RoadNetwork::RoadNetwork() {
	gv = NULL;

}

RoadNetwork::~RoadNetwork() {

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
	if(gv != NULL) {
		gv->closeWindow();
	}

	gv = new GraphViewer(GV_WIDTH, GV_HEIGHT, false);
	gv->setBackground("map.png");
	gv->createWindow(GV_WIDTH, GV_WIDTH);
	gv->defineVertexColor(DEFAULT_VERTEX_COLOR);
	gv->defineEdgeColor(DEFAULT_EDGE_COLOR);
	gv->defineVertexSize(5);

	vector<Vertex<int> *> vertexes = graph.getVertexSet();

	for (unsigned int i = 0; i < vertexes.size(); i++) {

		int x = resizeLon(vertexes[i]->getLongitude());
		int y = resizeLat(vertexes[i]->getLatitude());

		gv->addNode(vertexes[i]->getInfo(), x, y);

		gv->setVertexLabel(vertexes[i]->getInfo(), vertexes[i]->getName());


	}


	for(unsigned int i = 0; i < vertexes.size(); i++) {
		vector<Edge<int>*> edges = vertexes[i]->getAdj();
		for(unsigned int  j = 0; j < edges.size(); j++) {

			if(edges[j]->getTwoWays()) {
				if(edges[j]->getDest()->getInfo() > vertexes[i]->getInfo()) continue;
				gv->addEdge(edges[j]->getId(), vertexes[i]->getInfo(), edges[j]->getDest()->getInfo(), EdgeType::UNDIRECTED);
			}
			else {
				gv->addEdge(edges[j]->getId(), vertexes[i]->getInfo(), edges[j]->getDest()->getInfo(), EdgeType::DIRECTED);
			}
			//gv->setEdgeWeight(edges[j].getId(), edges[j].getWeight());
			//gv->setEdgeLabel(edges[j].getId(), edges[j].getName());
			if(edges[j]->getBlocked()) {
				gv->setEdgeColor(edges[j]->getId(), BLOCKED_EDGE_COLOR);
			}
			gv->setEdgeThickness(edges[j]->getId(), 5);
		}
	}

	gv->rearrange();

}

void RoadNetwork::updateMap() const {
	gv->rearrange();
}

const Graph<int>& RoadNetwork::getGraph() const {
	return graph;
}

bool RoadNetwork::getEdgeBlockedStatus(string name){
    /*for(size_t i  = 0; i < graph.getVertexSet().size(); i++){
    	for(size_t n = 0; n < graph.getVertexSet().at(i)->getAdj().size(); n++){
    		if(graph.getVertexSet().at(i)->getAdj().at(n)->getName() != "")
    			if(graph.getVertexSet().at(i)->getAdj().at(n)->getName() == name)
    				return graph.getVertexSet().at(i)->getAdj().at(n)->getBlocked();
    	}
    }
    return false;*/
	return this->graph.bfsEdgeBlocked(name);
}

void RoadNetwork::setEdgeBlocked(string edge_name, bool blocked){
    /*for(size_t i  = 0; i < graph.getVertexSet().size(); i++){
    	for(size_t n = 0; n < graph.getVertexSet().at(i)->getAdj().size(); n++){
    		if(graph.getVertexSet().at(i)->getAdj().at(n)->getName() != "")
    			if(graph.getVertexSet().at(i)->getAdj().at(n)->getName() == edge_name){
    				graph.setEdgeBlocked(graph.getVertexSet().at(i)->getAdj().at(n)->getId(),blocked);
    			}
    	}
    }*/
	this->graph.dfsSetEdgeBlocked(edge_name,blocked);
}

double RoadNetwork::getWeightOfPath(vector<Vertex<int>*> vec) {
	double totalWeight = 0;
	/*graph.dijkstraShortestPath(nodeStartID);
	vector<int> graphPath = graph.getPath(nodeStartID,nodeDestinationID);
	for(size_t i = 0; i < graphPath.size(); i++){
		for(size_t n = 0; n < graph.getVertex(graphPath.at(i))->getAdj().size(); n++){
			if(i < graphPath.size() - 1)
				if(graph.getVertex(graphPath.at(i))->getAdj().at(n)->getDest()->getName() == graph.getVertex(graphPath.at(i + 1))->getName())
					totalWeight += graph.getVertex(graphPath.at(i))->getAdj().at(n)->getWeight();
		}
	}*/
	for(auto v:vec)
	{
		if (v->getPath() != NULL) {
			totalWeight+=v->getCaminho()->getWeight();
		}
	}
	return totalWeight;
}

void RoadNetwork::printPath(int nodeStartID, int nodeDestinationID){

	this->graph.dijkstraShortestPath(nodeStartID);

	cout << endl;
	cout << "PERCURSO:" << endl;

	vector<Vertex<int>*> imprimir= this->graph.getPathVertex(nodeStartID,nodeDestinationID);

	for(auto it:imprimir)
	{
		if(it->getPath()!=NULL)
		{
			cout << it->getCaminho()->getName() << endl;
			this->highlightEdge(it->getCaminho()->getId());
		}
		cout << it->getName() << endl;
		this->highlightNode(it->getInfo());

	}

	cout << endl;

	cout << "DISTANCIA APROXIMADA DO PERCURSO: " << this->getWeightOfPath(imprimir) << " km" << endl;

}

void RoadNetwork::printAllCarPath() const
{
	cout << endl;
	for(auto car:this->graph.getCarro())
	{
		cout << "Carro " << car->getId() << " percurso:" << endl;
		for(unsigned int i=0;i<car->getNodesPath().size();i++)
		{
			cout << car->getNodesPath().at(i) << endl;
			if(i!=car->getNodesPath().size()-1){
				cout << car->getEdgePath().at(i) << endl;
			}
		}
	}
}

void RoadNetwork::highlightNode(int id) const {
	gv->setVertexColor(id, HIGHLIGHTED_VERTEX_COLOR);
}

void RoadNetwork::highlightEdge(int id) const {
	gv->setEdgeColor(id, HIGHLIGHTED_EDGE_COLOR);
	//gv->setEdgeThickness(id, 5);
}

void RoadNetwork::removeHighlightNode(int id) const {
	gv->setVertexColor(id, DEFAULT_VERTEX_COLOR);
}

void RoadNetwork::removeHighlightEdge(int id) const {
	gv->setEdgeColor(id, DEFAULT_EDGE_COLOR);
	//gv->setEdgeThickness(id, 1);

}

void RoadNetwork::blockEdge(int id) const {
	gv->setEdgeColor(id, BLOCKED_EDGE_COLOR);
}

void RoadNetwork::removeBlockEdge(int id) const {
	gv->setEdgeColor(id, DEFAULT_EDGE_COLOR);
}


//void RoadNetwork::highlightPath(vector<Vertex<int>* > p) const {
//	for(unsigned int i = 0; i < p.size(); i++) {
//		highlightNode(p[i]->getInfo());
//		if(i == p.size() - 1) continue;
//		vector<Edge<int> > edges = p[i]->getAdj();
//		for(unsigned int j = 0; j < edges.size(); j++) {
//			if(edges[j].getDest()->getInfo() == p[i]->getInfo()) {
//				highlightEdge(edges[j].getId());
//			}
//		}
//	}
//}
