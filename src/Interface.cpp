#include "Interface.h"

Interface::Interface() {
	roadnetwork = new RoadNetwork();
	roadnetwork->readOSM();
}

Interface::~Interface() {}

void Interface::convertToGV() {
	roadnetwork->convertToGV();
}

void Interface::roadsBlocked(){
    cout << "------------------------------" << endl;
    cout << "ALTERACAO DO ESTADO DE UMA VIA" << endl;
    cout << "------------------------------" << endl;
    cout << endl;
    set<string> nomes_estradas = roadnetwork->getGraph().getEdgesNames();
    set<string> nome_estradas_organizadas;
    set<string> subset_nome_estardas;

    set<string>::iterator it = nomes_estradas.begin();
    while(it != nomes_estradas.end()){
    	string nome = *it;
    	nome_estradas_organizadas.insert(nome.substr(0, nome.find(' ')));
    	it++;
    }

    int m = 0;
	set<string>::iterator itn = nome_estradas_organizadas.begin();
	while (itn != nome_estradas_organizadas.end()) {
		m++;
		cout << m << ". ";
		cout << *itn;
		cout << endl;
		itn++;
	}

    int opcao1;
    cout << endl;
    cout << "Indique o numero da estrada: ";
    cin >> opcao1;

    cout << endl;

    itn = nome_estradas_organizadas.begin();
    advance(itn, (opcao1 - 1));
    string opcao_string = (*itn);

    m = 0;
    int p = 0;
    vector<int> indices;
    it = nomes_estradas.begin();
    while(it != nomes_estradas.end()){
    	string n = (*it);
    	m++;
    	if(n.substr(0, n.find(' ')) == opcao_string){
    		p++;
    		cout << p << ". ";
    		indices.push_back(m - 1);
    		cout << n << endl;
    	}
    	it++;
    }

    int opcao2;
    cout << endl;
    cout << "Indique o troco da estrada: ";
    cin >> opcao2; // tem que ser menor que indices.size() e maior que 0

    it = nomes_estradas.begin();
    advance(it, indices.at(opcao2 -1));
    string nome_rua = *it;
    bool rua_bloqueada = roadnetwork->getEdgeBlockedStatus(nome_rua);
    cout << endl;
    if(rua_bloqueada){
    	cout << "Esta estrada encontra-se cortada." << endl;
    }
    else{
    	cout << "Esta estrada encontra-se transitavel." << endl;
    }
    char ch;
    cout << "Deseja altera o estado da estrada? (Y/N): ";
    cin >> ch;
    cout << endl;
    switch(ch){
    case 'Y':
    	roadnetwork->setEdgeBlocked(nome_rua, !rua_bloqueada);
    	cout << "Estado da rua alterado com sucesso!" << endl;
    	break;
    case 'y':
       	roadnetwork->setEdgeBlocked(nome_rua, !rua_bloqueada);
       	cout << "Estado da rua alterado com sucesso!" << endl;
       	break;
    case 'n':
    	break;
    case 'N':
    	break;
    default:
    	cout << "Opcao invalida.";
    	break;
    }
    roadnetwork->writeEdgeFile();
    roadnetwork->updateInfo();
    returnMenu2();
}

void Interface::calculatePath(){
    cout << "-----------------" << endl;
    cout << "CALCULAR PERCURSO" << endl;
    cout << "-----------------" << endl;
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
    //roadnetwork->updateInfo();
    returnMenu();
}

void Interface::showMap(){
	cout << "Mapa a ser gerado..." << endl;
	convertToGV();
	returnMenu();
}

void Interface::getAllCarsPath(){
    cout << "-------------------" << endl;
    cout << "PERCURSO DOS CARROS" << endl;
    cout << "-------------------" << endl;
    cout << endl;
	roadnetwork->printAllCarPath();
	returnMenu2();
}

void Interface::removeCar(){
    cout << "--------------" << endl;
    cout << "REMOVER CARRO" << endl;
    cout << "-------------" << endl;
    cout << endl;
    roadnetwork->printCarID();
    cout << endl;
    int opcao;
    cout << "Indique o numero do carro que deseja remover: ";
    cin >> opcao;
    roadnetwork->removeCar(opcao);
    cout << endl << "Carro removido com sucesso." << endl;
    roadnetwork->writeCarsFile();
    roadnetwork->updateInfo();
	returnMenu2();
}

void Interface::updateMap() {
	roadnetwork->updateMap();
}

void Interface::closeMapWindow(){
	roadnetwork->closeMapWindow();
}

void Interface::returnMenu(){
	cout << endl;
	int opcao;
	cout << "[1] Voltar ao menu principal." << endl;
	cout << "[0] Sair" << endl;
	cout << endl;
	cout << "Escolha uma opcao: ";
	cin >> opcao;
	if(opcao == 1){
		this->closeMapWindow();
		cout << endl << "Voltando ao menu principal..." << endl << endl;
		sleep(1);
	}
	else if (opcao == 0){
		this->closeMapWindow();
		exit(0);
	}
}

void Interface::returnMenu2(){
	cout << endl;
	int opcao;
	cout << "[1] Voltar ao menu principal." << endl;
	cout << "[0] Sair" << endl;
	cout << endl;
	cout << "Escolha uma opcao: ";
	cin >> opcao;
	if(opcao == 1){
		cout << endl << "Voltando ao menu principal..." << endl << endl;
		sleep(1);
	}
	else if (opcao == 0){
		this->closeMapWindow();
		exit(0);
	}
}

void Interface::writeFiles()
{
	this->roadnetwork->writeCarsFile();
	this->roadnetwork->writeEdgeFile();
}
