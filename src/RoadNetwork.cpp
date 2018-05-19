#include "RoadNetwork.h"

const unsigned int cost_del = 1 , cost_ins = 1 , cost_sub = 1;

RoadNetwork::RoadNetwork() {
	gv = NULL;

}

RoadNetwork::~RoadNetwork() {

}

void RoadNetwork::readOSM() {
	string nodesFile = "nodes.txt";
	string edgesFile = "edges.txt";
	string connectionsFile = "connections.txt";
	string carFiles= "cars.txt";

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
	bool two_ways = false;
	bool blocked;

	while (getline(fEdges, line)) {
		string data;
		istringstream linestream(line);

		getline(linestream, data, ';');
		id = atof(data.c_str());
		getline(linestream, data, ';');
		name = data;
		getline(linestream, data, ';');
		if(data == "True")
			blocked = true;
		else
			blocked = false;

		for(unsigned int i = 0; i < links.size(); i++) {
			if(links.at(i).edgeID == id) {
				double w = graph.calculateDist(links.at(i).nodeID1, links.at(i).nodeID2);

				graph.addEdge(links.at(i).nodeID1, links.at(i).nodeID2, w, two_ways, name, id, blocked);
				graph.addEdge(links.at(i).nodeID2, links.at(i).nodeID1, w, two_ways, name, id*-1, blocked);
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

			if (w->getDest()->getInfo() > v->getInfo())
				continue;
			gv->addEdge(w->getId(), v->getInfo(),
					w->getDest()->getInfo(), EdgeType::DIRECTED);
			gv->addEdge(w->getId()*-1, w->getDest()->getInfo(),
									v->getInfo(), EdgeType::DIRECTED);
			gv->setEdgeThickness(w->getId(), 5);
			gv->setEdgeThickness(w->getId()*-1, 5);
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

	this->convertToGV();

	graph.addCar(nodeStartID, nodeDestinationID, this->graph.getCarros().size());

	cout << endl;
	cout << "PERCURSO:" << endl;

	vector<Vertex<int>*> imprimir= graph.getCarros().at(graph.getCarros().size()-1)->getNodesPath();

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
}

void RoadNetwork::printAllCarPath() const
{
	for(auto car:this->graph.getCarros())
	{
		cout << "CARRO " << car->getId() << endl << "Percurso:" << endl;
		if(!car->isTemPercurso()){
			cout << "Este carro nao tem percurso possivel." << endl;
		}
		else {
			for (unsigned int i = 0; i < car->getNodesPath().size(); i++) {
				cout << "-->" << car->getNodesPath().at(i)->getName() << endl;
				if (i != car->getNodesPath().size() - 1) {
					cout << " - " << car->getEdgePath().at(i)->getName() << endl;
				}
			}
		}
		cout << endl;
	}
}

void RoadNetwork::printCarID() const{
	for(auto car:this->graph.getCarros())
	{
		cout << "CARRO " << car->getId() << endl << "Percurso: ";
		if(!car->isTemPercurso()){
			cout << "Este carro nao tem percurso possivel.";
		}
		else {
			cout << car->getNodesPath().at(0)->getName();
			cout << " - ";
			cout << car->getNodesPath().at(car->getNodesPath().size()-1)->getName();
		}
		cout << endl;
	}
}

bool RoadNetwork::removeCar(int id){
	return graph.removeCar(id);
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

bool compareVectorEdges(Edge<int>* edge1, Edge<int>* edge2){
	return edge1->getId() < edge2->getId();
}

void RoadNetwork::writeEdgeFile(){
	ofstream edgefile;
	edgefile.open("edges.txt");
	vector <Edge<int> *> guardar = graph.getEdges();
	sort(guardar.begin(),guardar.end(),compareVectorEdges);
	size_t m = 0;
	for(auto i : guardar){
		m++;
		edgefile << i->getId( ) << ";" << i->getName() << ";";
		if(i->getBlocked())
			edgefile << "True";
		else
			edgefile << "False";
		if(m < guardar.size())
			edgefile << endl;
	}
	edgefile.close();
}

void RoadNetwork::writeCarsFile(){
	ofstream carfile;
	carfile.open("cars.txt");
	vector<Carro<int>*> guardar = graph.getCarros();
	size_t m = 0;
	for(auto i : guardar){
		m++;
		carfile << i->getId() << ";" << i->getIdInicio() << ";" << i->getIdFim();
		if(m < guardar.size())
			carfile << endl;
	}
	carfile.close();
}

void RoadNetwork::updateInfo(){
	graph.eraseAll();
	readOSM();
}

vector<int> cpf(string pattern){
	int m = pattern.length();
	vector<int> prefix(m);
	prefix[0] = -1;
	int k = -1;
	for(int q = 1; q < m; q++){
		while(k > -1 && tolower(pattern[k+1]) != tolower(pattern[q])) {
			k = prefix[k];
		}
		if(tolower(pattern[k+1]) == tolower(pattern[q]))
			k = k+1;
		prefix[q] = k;
	}
	return prefix;
}

int kmpMatcher(string text, string pattern) {
	int num = 0;
	int n = text.length();
	int m = pattern.length();
	vector<int> prefix = cpf(pattern);
	int q = -1;
	for(int i = 0; i < n; i++){
		while(q > -1 && tolower(pattern[q+1]) != tolower(text[i]))
			q = prefix[q];
		if(tolower(pattern[q+1]) == tolower(text[i]))
			q++;
		if(q == m-1){
			num++;
			q = prefix[q];
		}
	}
	return num;
}

int editDistance(string pattern, string text) {
	int n = text.length();
	int m = pattern.length();
	int old_value, new_value;
	int d[n+1];

	for(int j = 0; j < n+1; j++){
		d[j] = j;
	}

	for(int i = 1; i < m+1; i++){
		old_value = d[0];
		d[0] = 1;
		for(int j = 1; j < n + 1; j++){
			if(tolower(pattern[i-1]) == tolower(text[j-1]))
				new_value = old_value;
			else{
				new_value = min(old_value,d[j]);
				new_value = 1 + min(new_value,d[j-1]);
			}
			old_value = d[j];
			d[j] = new_value;
		}
	}
	return d[n];
}

unsigned int levenshtein(const string & s1, const string & s2) {
    unsigned int i,j, n1 = s1.length() , n2 = s2.length();
    unsigned int * p = new unsigned int[n2+1] , * q = new unsigned int[n2+1];

    p[0] = 0;
    for( j = 1; j <= n2; ++j )
        p[j] = p[j-1] + cost_ins;

    for( i = 1; i <= n1; ++i )
    {
        q[0] = p[0] + cost_del;
        for( j = 1; j <= n2; ++j )
        {
            unsigned int d_del = p[j] + cost_del;
            unsigned int d_ins = q[j-1] + cost_ins;
            unsigned int d_sub = p[j-1] + ( tolower(s1[i-1]) == tolower(s2[j-1]) ? 0 : cost_sub );
            q[j] = min( min( d_del, d_ins ), d_sub );
        }
        unsigned int * temp = p;
        p = q;
        q = temp;
    }
    unsigned int dist = p[n2];
    delete[] p;  delete[] q;

    return dist;
}

void RoadNetwork::exactEdgeSearch(string estrada) {
	string nome;
	int counter = 0;
	set<string> nomes_estradas = graph.getEdgesNames();
	set<string>::iterator it = nomes_estradas.begin();
	set<string> nomes_estradas_semelhantes;
	while(it != nomes_estradas.end()){
		nome = *it;
		if(kmpMatcher(nome, estrada) == 1){
			nomes_estradas_semelhantes.insert(nome);
		}
		counter++;
		it++;
	}

	if(nomes_estradas_semelhantes.size() == 0)
		cout << endl << "Estrada desconhecida!" << endl;
	else{
		int m = 1;
		set<string>::iterator itr = nomes_estradas_semelhantes.begin();
		while(itr != nomes_estradas_semelhantes.end()){
			nome = *itr;
			cout << "[" << m << "] ";
			cout << nome << endl;
			m++;
			itr++;
		}

		int opcao = -1;
		cout << endl;
		cout << "Indique o nome da estrada onde se encontra: ";
		while (!(cin >> opcao) || opcao < 1 || opcao > m - 1) {
			cout << "Opcao invalida! Escolha uma nova opcao: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		itr = nomes_estradas_semelhantes.begin();
		advance(itr, opcao - 1);
		nome = *itr;

		setEdgeBlocked(nome, true);

		cout << endl << "A estrada " << nome << " foi cortada com sucesso e foi calculada uma rota de evacuação para todos os carros." << endl;
	}
	writeEdgeFile();
	updateInfo();
}

void RoadNetwork::approximateEdgeSearch(string estrada, int op) {
	set<string> nomes_estradas = graph.getEdgesNames();
	set<string>::iterator it = nomes_estradas.begin();

	int counter = 0;
	vector<pair<int,string>> nomes_estradas_semelhantes;

	while(it != nomes_estradas.end()){
		string nome = *it;
		string road_name;
		string first_point;
		string second_point;

		road_name = nome.substr(0, nome.find(" (", 0) - 0);
		first_point = nome.substr(road_name.length() + 2, nome.find(" -", 0) - road_name.length() - 2);
		second_point = nome.substr(road_name.length() + 5 +first_point.length(), nome.find(")", 0) - (road_name.length() + 5 +first_point.length()));

		int adicionar;

		if(op == 1) counter += editDistance(road_name, estrada);
		else counter += levenshtein(road_name, estrada);

        if(op == 1) adicionar = editDistance(first_point, estrada);
        else adicionar = levenshtein(first_point, estrada);
        if (adicionar > 4){
            counter += adicionar;
        }
        
        if (op == 1) adicionar = editDistance(second_point, estrada);
        else adicionar = levenshtein(second_point, estrada);
        if (adicionar > 4){
            counter += adicionar;
        }


		nomes_estradas_semelhantes.push_back(make_pair(counter, nome));
		counter = 0;
		it++;
	}

	sort(nomes_estradas_semelhantes.begin(), nomes_estradas_semelhantes.end());

	//só os 10 melhores resultados
	cout << endl;
	for(int i = 0; i < 10; i++){
		cout << "[" << i + 1 << "] ";
		cout << nomes_estradas_semelhantes.at(i).second << endl;
	}
	cout << "[0] Nenhum\n";

    int opcao = -1;
    cout << endl;
    cout << "Indique o nome da estrada onde se encontra: ";
    while (!(cin >> opcao) || opcao < 0 || opcao > 10) {
        cout << "Opcao invalida! Escolha uma nova opcao: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if(opcao != 0) {
		string nome = nomes_estradas_semelhantes.at(opcao - 1).second;

		setEdgeBlocked(nome, true);
		cout << endl << "A estrada " << nome << " foi cortada com sucesso e foi calculada uma rota de evacuação para todos os carros." << endl;

		writeEdgeFile();
		updateInfo();
    }
}