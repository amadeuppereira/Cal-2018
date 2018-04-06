#include "menu.h"

using namespace std;

void menu() {

	Interface i = Interface();

    while(1){
        int option = -1;
        if(option < 0 || option > 5){
            cout << "--------------------" << endl;
            cout << "SISTEMA DE EVACUACAO" << endl;
            cout << "--------------------" << endl;
            cout << endl;
            cout << "[1] Alterar Estado das Estradas" << endl;
            cout << "[2] Calcular Itinerarios" << endl;
            cout << "[3] Ver Percursos dos Carros" << endl;
            cout << "[4] Remover Carro" << endl;
            cout << "[5] Ver Mapa" << endl;
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
                break;
            case 3:
            	i.getAllCarsPath();
                break;
            case 4:
            	i.removeCar();
            	break;
            case 5:
            	i.showMap();
            	break;
            default:
                while(option < 0 || option > 5){
                    cout << "Opcao invalida! Escolha uma nova opcao: ";
                    cin >> option;
                }
                break;
        }
    }
}
