#include "Interface.h"

Interface::Interface() {
	this->destinyID = 0;
	this->sourceID = 0;
	roadnetwork = new RoadNetwork();
	roadnetwork->readOSM();
	convertToGV();

}

Interface::~Interface() {}

void Interface::convertToGV() {
	roadnetwork->convertToGV();
}

unsigned long long Interface::getDestinyId() const {
	return destinyID;
}

void Interface::setDestinyId(int destinyId) {
	destinyID = destinyId;
}

unsigned long long Interface::getSourceId() const {
	return sourceID;
}

void Interface::setSourceId(int sourceId) {
	sourceID = sourceId;
}

void Interface::roadsBlocked(){
    cout << "------------------------------" << endl;
    cout << "ALTERACAO DO ESTADO DE UMA VIA" << endl;
    cout << "------------------------------" << endl;
    cout << endl;

    set<string> nomes_ruas = roadnetwork->getGraph().getEdgesNames();

    int m = 0;
    set<string>::iterator it = nomes_ruas.begin();
    while(it != nomes_ruas.end()){
    	m++;
    	cout << m << ". ";
    	cout << *it;
    	cout << endl;
    	it++;
    }

    int opcao;
    cout << endl;
    cout << "Indique o numero da rua: ";
    cin >> opcao;

    it = nomes_ruas.begin();
    advance(it, (opcao -1));
    string nome_rua = *it;
    bool rua_bloqueada = roadnetwork->getEdgeBlockedStatus(nome_rua);
    cout << endl;
    if(rua_bloqueada){
    	cout << "Esta rua encontra-se cortada." << endl;
    }
    else{
    	cout << "Esta rua encontra-se transitavel." << endl;
    }
    char ch;
    cout << "Deseja altera o estado da rua? (Y/N): ";
    cin >> ch;
    switch(ch){
    case 'Y':
    	roadnetwork->setEdgeBlocked(nome_rua, !rua_bloqueada);
    	cout << "Estado da rua alterado com sucesso" << endl;
    	break;
    case 'y':
       	roadnetwork->setEdgeBlocked(nome_rua, !rua_bloqueada);
       	cout << "Estado da rua alterado com sucesso" << endl;
       	break;
    case 'n':
    	break;
    case 'N':
    	break;
    default:
    	cout << "Opcao invalida.";
    	break;
    }
}

void Interface::calculatePath(){
    cout << "-----------------------------------" << endl;
    cout << "PERCURSO DE UMA ORIGEM A UM DESTINO" << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;

    for(unsigned int i = 0; i < roadnetwork->getGraph().getVertexSet().size(); i++){
    	cout << i + 1 << ". " << roadnetwork->getGraph().getVertexSet().at(i)->getName() << endl;
    }
    int origem, destino;
    cout << endl;
    cout << "Indique a origem do percurso: ";
    cin >> origem;
    while(origem > roadnetwork->getGraph().getVertexSet().size() || origem < 1){
    	cout << "Opcão Inválida. Introduza uma nova origem: ";
    	cin.clear();
    	cin.ignore(1000, '\n');
    	cin >> origem;
    }
    cout << "Indique o destino do percurso: ";
    cin >> destino;
    while(destino > roadnetwork->getGraph().getVertexSet().size() || destino < 1){
    	cout << "Opcao Invalida. Introduza um novo destino: ";
    	cin.clear();
    	cin.ignore(1000, '\n');
    	cin >> destino;
    }

    origem = roadnetwork->getGraph().getVertexSet().at(origem - 1)->getInfo();
    destino = roadnetwork->getGraph().getVertexSet().at(destino - 1)->getInfo();

    this->roadnetwork->printPath(origem,destino);

    /*cout << endl;
    cout << "PERCURSO:" << endl;
    vector<Vertex<int>* > nodes_path = roadnetwork->getNodesPathVector(origem, destino);
    vector<Edge<int> > edges_path = roadnetwork->getEdgesPathVector(origem, destino);
    for(unsigned int i = 0; i < nodes_path.size(); i++){
    	roadnetwork->highlightNode(nodes_path.at(i)->getInfo());
    	cout << "---> " << nodes_path.at(i)->getName() << endl;
    	if(i < nodes_path.size() - 1) {
    		roadnetwork->highlightEdge(edges_path.at(i).getId());
    		cout << "  - " << edges_path.at(i).getName() << endl;
    	}
    }
    cout << endl;

    cout << "DISTANCIA APROXIMADA DO PERCURSO: " << roadnetwork->getWeightOfPath(origem, destino) << " km" << endl;*/
}

void Interface::updateMap() {
	roadnetwork->updateMap();
}