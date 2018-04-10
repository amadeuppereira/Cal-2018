#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include "RoadNetwork.h"
#include <set>
#include <unistd.h>

class Interface {
private:
	/**
	 * Variavel que guarda a roadnetwork
	 */
	RoadNetwork* roadnetwork;
public:
	/**
	 * Construtor da classe Interface
	 */
	Interface();

	/**
	 * Destrutor da classe Interface
	 */
	virtual ~Interface();

	/**
	 *	Chama a função convertToGV da classe RoadNetwork
	 */
	void convertToGV();

	/**
	 *	Altera o estado de uma via, sendo possível cortá-la ou torná-la transitável
	 */
	void roadsBlocked();

	/**
	 * Calcula o caminho entre uma origem e um destino
	 */
	void calculatePath();

	/**
	 *	Mostra o mapa do GraphViewer
	 */
	void showMap();

	/**
	 *	Atualiza o mapa
	 */
	void updateMap();

	/**
	 *	Fecha o mapa do GraphViewer
	 */
	void closeMapWindow();

	/**
	 *	Mostra a informação do percurso de todos os carros
	 */
	void getAllCarsPath();

	/**
	 *	Remove um carro pelo ID
	 */
	void removeCar();

	/**
	 *	Volta ao menu inicial
	 */
	void returnMenu();

	/**
	 *	Volta ao menu inicial
	 */
	void returnMenu2();

	/**
	 *	Guarda as informações nos ficheiros de texto correspondentes
	 */
	void writeFiles();
};

#endif /* SRC_INTERFACE_H_ */
