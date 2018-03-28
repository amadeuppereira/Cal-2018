#include "menu.h"

using namespace std;

void menu () {

    while(1){
        int option = -1;
        cout << endl;
        if(option < 0 || option > 3){
            cout << "--------------------" << endl;
            cout << "SISTEMA DE EVACUACAO" << endl;
            cout << "--------------------" << endl;
            cout << endl;
            cout << "[1] Rotas" << endl;
            cout << "[2] Trocos" << endl;
            cout << "[3] Ver mapa" << endl;
            cout << "[0] Sair" << endl;
            cout << endl;
            cout << "Escolha uma opcao: ";
            cin >> option;
        }

        switch(option){
            case 0:
                return;
            case 1:
                submenu_1 ();
                break;
            case 2:
                submenu_2 ();
                break;
            case 3:
                // Ver mapa
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

void submenu_1 (){
    while(1) {
        int option = -1;
        cout << endl;
        if (option < 0 || option > 2) {
            cout << "-----" << endl;
            cout << "ROTAS" << endl;
            cout << "-----" << endl;
            cout << endl;
            cout << "[1] Calcular rota" << endl;
            cout << "[2] Atualizar rotas" << endl;
            cout << "[0] Voltar ao menu inicial." << endl;
            cout << endl;
            cout << "Escolha uma opcao: ";
            cin >> option;
        }

        switch (option) {
            case 0:
                return;
            case 1:
                //Calcular a rota
                break;
            case 2:
                //Atualizar rotas
                break;
            default:
                while (option < 0 || option > 2) {
                    cout << "Opcao invalida! Escolha uma nova opcao: ";
                    cin >> option;
                }
                break;
        }
    }
}

void submenu_2 (){
    while(1) {
        int option = -1;
        cout << endl;
        if (option < 0 || option > 2) {
            cout << "------" << endl;
            cout << "TROCOS" << endl;
            cout << "------" << endl;
            cout << endl;
            cout << "[1] Criar novo troco" << endl;
            cout << "[2] Atualizar troco" << endl;
            cout << "[0] Voltar ao menu inicial." << endl;
            cout << endl;
            cout << "Escolha uma opcao: ";
            cin >> option;
        }

        switch (option) {
            case 0:
                return;
            case 1:
                //Criar novo troco
                break;
            case 2:
                //Atualizar troco
                break;
            default:
                while (option < 0 || option > 2) {
                    cout << "Opcao invalida! Escolha uma nova opcao: ";
                    cin >> option;
                }
                break;
        }
    }
}