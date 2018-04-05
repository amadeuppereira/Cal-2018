#include "menu.h"

using namespace std;

void menu() {

	Interface i = Interface();

    while(1){
        int option = -1;
        if(option < 0 || option > 3){
            cout << "--------------------" << endl;
            cout << "SISTEMA DE EVACUACAO" << endl;
            cout << "--------------------" << endl;
            cout << endl;
            cout << "[1] Alterar Estado das Estradas" << endl;
            cout << "[2] Calcular Itinerarios" << endl;
            cout << "[3] Ver Percursos dos Carros" << endl;
            cout << "[4] Ver Mapa" << endl;
            cout << "[0] Sair" << endl;
            cout << endl;
            cout << "Escolha uma opcao: ";
            cin >> option;
            cout << endl;
        }

        switch(option){
            case 0:
            	exit(0);
                return;
            case 1:
            	i.roadsBlocked();
                break;
            case 2:
            	i.calculatePath();
                //ao alterar o estado das estradas temos de atualizar as rotas dos carros
                break;
            case 3:
            	i.carros();
                break;
            case 4:
            	i.showMap();
            	break;
            default:
                while(option < 0 || option > 3){
                    cout << "Opcao invalida! Escolha uma nova opcao: ";
                    cin >> option;
                }
                break;
        }
    }
}
