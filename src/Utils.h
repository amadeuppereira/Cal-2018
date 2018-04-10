#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <vector>
#include <float.h>
#include "Graph.h"
#include "math.h"

#define GV_WIDTH 1157
#define GV_HEIGHT 2405

#define MIN_LON -9.5691
#define MAX_LON -6.3940
#define MIN_LAT 36.8554
#define MAX_LAT 41.9411

/**
 * Classe que guarda informacao relativa as relacoes entres as edges e os
 * vertices iniciais e finais das mesas
 */
class Link {
public:
	/**
	 * Variavel que guarda o id da edge
	 */
	int edgeID;
	/**
	 * Variavel que guarda o id do vertice inicial da edge
	 */
	int nodeID1;
	/**
	 * Variavel que guarda o id do vertice final da edge
	 */
	int nodeID2;
	/**
	 * Construtor da class Link
	 * @param e id da edge
	 * @param n1 id do vertice inicial
	 * @param n2 id do vertice final
	 */
	Link(int e, int n1, int n2) {
		edgeID = e;
		nodeID1 = n1;
		nodeID2 = n2;
	}
};

/**
 * Calcula a posicao relativa, no mapa, da latitude dada, tendo por base o tamanho
 * do mapa e as suas coordenadas extremas
 * @param lat latitude
 * @return nova posicao
 */
int resizeLat(long double lat);

/**
 * Calcula a posicao relativa, no mapa, da longitude dada, tendo por base o tamanho
 * do mapa e as suas coordenadas extremas
 * @param lon longitude
 * @return nova posicao
 */
int resizeLon(long double lon);




#endif /* SRC_UTILS_H_ */
