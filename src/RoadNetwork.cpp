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
	string carFiles= "carros.txt";

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
	bool two_ways = true;
	bool blocked = false;

	while (getline(fEdges, line)) {
		string data;
		istringstream linestream(line);

		getline(linestream, data, ';');
		id = atof(data.c_str());
		getline(linestream, data, ';');
		name = data;

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


	ifstream fCars;
	fCars.open(carFiles);
	if (!fCars) {
		cerr << "Unable to open file " << carFiles << endl;
		exit(1);
	}

	int inicio,fim;

	while (getline(fCars, line)) {
		string data;
		istringstream linestream(line);

		getline(linestream, data, ';');
		id = atof(data.c_str());
		getline(linestream, data, ';');
		inicio = atof(data.c_str());
		getline(linestream, data, ';');
		fim = atof(data.c_str());

		this->graph.addCar(inicio,fim,id);
	}
	fCars.close();
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
	for (auto v:this->graph.getVertexSet()) {
		int x = resizeLon(v->getLongitude());
		int y = resizeLat(v->getLatitude());

		gv->addNode(v->getInfo(), x, y);

		for (auto w:v->getAdj()) {

			if (w->getTwoWays()) {
				if (w->getDest()->getInfo() > v->getInfo())
					continue;
				gv->addEdge(w->getId(), v->getInfo(),
						w->getDest()->getInfo(), EdgeType::UNDIRECTED);
			} else {
				gv->addEdge(w->getId(), v->getInfo(),
						w->getDest()->getInfo(), EdgeType::DIRECTED);
			}
			gv->setEdgeThickness(w->getId(), 5);
		}
	}
	updateMap();
	gv->rearrange();

}

void RoadNetwork::updateMap() const {
	for(auto v:this->graph.getVertexSet())
	{
		for(auto w:v->getAdj())
		{
			if (w->getQuantidade() >= MAX_CAPACITY / 2) {
				if (w->getQuantidade() >= MAX_CAPACITY)
					gv->setEdgeColor(w->getId(), HIGH_TRAFFIC);
				else
					gv->setEdgeColor(w->getId(), MEDIUM_TRAFFIC);
			}
			if (w->getBlocked()) {
				gv->setEdgeColor(w->getId(), BLOCKED_EDGE_COLOR);
			}
		}
	}
	gv->rearrange();
}

const Graph<int>& RoadNetwork::getGraph() const {
	return graph;
}

bool RoadNetwork::getEdgeBlockedStatus(string name){
	return this->graph.bfsEdgeBlocked(name);
}

void RoadNetwork::setEdgeBlocked(string edge_name, bool blocked){
	this->graph.dfsSetEdgeBlocked(edge_name,blocked);
}

double RoadNetwork::getWeightOfPath(vector<Vertex<int>*> vec) {
	double totalWeight = 0;
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
	this->convertToGV();

	cout << endl;
	cout << "PERCURSO:" << endl;

	vector<Vertex<int>*> imprimir= this->graph.getPathVertex(nodeStartID,nodeDestinationID);

	if(imprimir.size() == 0){
		cout << "Impossivel calcular um percurso porque as estradas de ligacao ou estao cortadas ou estao congestionadas." << endl;
	}
	else {
		for (auto it : imprimir) {
			if (it->getPath() != NULL) {
				cout << "  - " << it->getCaminho()->getName() << endl;
				this->highlightEdge(it->getCaminho()->getId());
			}
			cout << "--> " << it->getName() << endl;
			this->highlightNode(it->getInfo());

		}

		cout << endl;

		cout << "DISTANCIA APROXIMADA DO PERCURSO: "
				<< this->getWeightOfPath(imprimir) << " km" << endl;

	}
	cout << endl;
	int opcao;
	cout << "[1] Voltar ao menu principal." << endl;
	cout << "[0] Sair" << endl;
	cout << endl;
	cout << "Escolha uma opcao: ";
	cin >> opcao;
	if(opcao == 2){
		closeMapWindow();
		cout << endl << "Voltando ao menu principal..." << endl << endl;
		sleep(1);
	}
	else if (opcao == 0){
		closeMapWindow();
		exit(0);
	}
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

void RoadNetwork::updateCarsPath(){
	graph.updateAllCarPath();
}

void RoadNetwork::highlightNode(int id) const {
	gv->setVertexColor(id, HIGHLIGHTED_VERTEX_COLOR);
}

void RoadNetwork::highlightEdge(int id) const {
	gv->setEdgeColor(id, HIGHLIGHTED_EDGE_COLOR);
}

void RoadNetwork::removeHighlightNode(int id) const {
	gv->setVertexColor(id, DEFAULT_VERTEX_COLOR);
}

void RoadNetwork::removeHighlightEdge(int id) const {
	gv->setEdgeColor(id, DEFAULT_EDGE_COLOR);
}

void RoadNetwork::blockEdge(int id) const {
	gv->setEdgeColor(id, BLOCKED_EDGE_COLOR);
}

void RoadNetwork::removeBlockEdge(int id) const {
	gv->setEdgeColor(id, DEFAULT_EDGE_COLOR);
}

void RoadNetwork::closeMapWindow() const{
	gv->closeWindow();
}
