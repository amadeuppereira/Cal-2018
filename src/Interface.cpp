#include "Interface.h"

Interface::Interface() {
	roadnetwork = new RoadNetwork();
	roadnetwork->readOSM();
	//roadnetwork->convertToGV();
}

Interface::~Interface() {}

void Interface::roadsBlocked(){
    cout << "------------------------------" << endl;
    cout << "ALTERACAO DO ESTADO DE UMA VIA" << endl;
    cout << "------------------------------" << endl;
    cout << endl;

    set<string> nomes_ruas = roadnetwork->getEdgesNames();

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
    	cout << "Esta rua encontra-se transitável." << endl;
    }
    char ch;
    cout << "Deseja altera o estado da rua? (Y/N): ";
    cin >> ch;
    switch(ch){
    case 'y':
    	roadnetwork->setEdgeBlocked(nome_rua, !rua_bloqueada);
    	cout << "Estado da rua alterado com sucesso" << endl;
    	break;
    case 'Y':
       	roadnetwork->setEdgeBlocked(nome_rua, !rua_bloqueada);
        cout << "Estado da rua alterado com sucesso" << endl;
    	break;
    case 'n':
    	break;
    case 'N':
    	break;
    default:
    	cout << "Opção inválida.";
    	break;
    }

    roadsBlocked();

}
