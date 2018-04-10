/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <set>
#include <list>
#include <limits>
#include <climits>

#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;
template <class T> class Carro;

#define INF std::numeric_limits<double>::max()
/**
 * Capacidade maxima das arestas
 */
#define MAX_CAPACITY 10


/*
 * ================================================================================================
 * Class Carro
 * ================================================================================================
 */
/**
 * class que representa um carro do grafo
 */
template <class T>
class Carro {
	/**
	 * Id de inicio do percurso do carro
	 */
	T id_inicio;
	/**
	 * id de destino do carro
	 */
	T id_fim;
	/**
	 * id do carro
	 */
	T id;
	/**
	 * vetor de vertices do caminho do carro
	 */
	vector<Vertex<T>*> nodes_path;
	/**
	 * vetor de arestas do caminho do carro
	 */
	vector<Edge<T>*> edge_path;
	/**
	 * true caso o carro tenha percurso, false caso contrario
	 */
	bool tem_percurso = true;
public:
	/**
	 * Construtor da class Carro, cria um novo carro com os parametros indicados
	 * @param id_inicio id de inicio do percurso
	 * @param id_fim id de fim do percurso
	 * @param id id do veiculo
	 */
	Carro(T id_inicio,T id_fim,T id);
	/**
	 *
	 * @return returna o caminho pelas arestas
	 */
	const vector<Edge<T> *>& getEdgePath() const {return edge_path;}
	/**
	 * Faz com que o edge_path do carro seja o que eu pretendo
	 * @param edgePath vector<Edge<T>*> que pretendo atribuir para o carro
	 */
	void setEdgePath(const vector<Edge<T> *>& edgePath) {edge_path = edgePath;}
	/**
	 *
	 * @return returna o id de destino do carro
	 */
	T getIdFim() const {return id_fim;}
	/**
	 * Coloca o id de destino que eu pertendo para o carro
	 * @param idFim id de destino que quero que o carro tenha
	 */
	void setIdFim(T idFim) {id_fim = idFim;}
	/**
	 *
	 * @return returna o id de incio do carro
	 */
	T getIdInicio() const {return id_inicio;}
	/**
	 * Coloca o id de inicio do carro para o que pretendo
	 * @param idInicio id de inicio que eu quero que o carro tenha
	 */
	void setIdInicio(T idInicio) {id_inicio = idInicio;}
	/**
	 *
	 * @return returna o vector<Vertex<T>*> do carro
	 */
	const vector<Vertex<T> *>& getNodesPath() const {return nodes_path;}
	/**
	 * Define a variavel nodes_path para o que eu pretendo
	 * @param nodesPath o vector de vertexs para qual eu pretendo mudar
	 */
	void setNodesPath(const vector<Vertex<T> *>& nodesPath) {nodes_path = nodesPath;}
	/**
	 *
	 * @return returna o valor da variavel tem_percurso, true se o carro tem um valor atribuido ou false caso contrario
	 */
	bool isTemPercurso() const {return tem_percurso;}
	/**
	 * Define se o carro tem percurso ou não atribuido
	 * @param temPercurso boolean do valor que quero atribuir
	 */
	void setTemPercurso(bool temPercurso = true) {tem_percurso = temPercurso;}
	/**
	 *
	 * @return returna o id do carro
	 */
	T getId() const {return id;}
	/**
	 * Define o id do carro
	 * @param id o id que eu quero que o carro tenha
	 */
	void setId(T id) {this->id = id;}
	friend class Graph<T>;
};
template<class T>
Carro<T>::Carro(T id_inicio, T id_fim, T id):id_inicio(id_inicio), id_fim(id_fim), id(id) {

}



/*
 * ================================================================================================
 * Class Vertex - InterseÃ§Ãµes
 * ================================================================================================
 */
/**
 * class que representa um vertice do grafo
 */
template <class T>
class Vertex {
	/**
	 * informação do vertice
	 */
	T info;
	/**
	 * vetor de arestas do vertice
	 */
	vector<Edge<T>*> adj;
	/**
	 * guarda o estado caso tenha o vertice tenha sido visitado
	 */
	bool visited;
	/**
	 * indegree do vertice para a ordenação topologica
	 */
	int indegree;
	/**
	 * nome do vertice
	 */
	string name;
	/**
	 * latitude do vertice
	 */
	double latitude;
	/**
	 * longitude do vertice
	 */
	double longitude;
	/**
	 * distancia do vertice
	 */
	double dist = 0;
	/**
	 * caminho para o proximo vertice
	 */
	Vertex<T> *path = NULL;
	/**
	 * caminho para a procima aresta
	 */
	Edge<T> *caminho = NULL;
	/**
	 * index para a mutablepriorityqueu
	 */
	int queueIndex = 0;
public:
	/**
	 * construtor da class Vertex
	 * @param in informação do vertice
	 * @param name nome do vertice
	 * @param lon londitude do vertice
	 * @param lat latitude do vertice
	 */
	Vertex(T in, string name, double lon, double lat);
	/**
	 * Overload do operador < para a class mutablepriorityqueue
	 * @param vertex vertice que quero comparar
	 * @return boolean true de dist<dist ou false caso contrario
	 */
	bool operator<(Vertex<T> & vertex) const;
	/**
	 *
	 * @return returna a informação do vertice
	 */
	T getInfo() const;
	/**
	 *
	 * @return returna o vector de arestas do vertice
	 */
	vector<Edge<T>*> getAdj() const;
	/**
	 * Adiciona uma aresta nova ao vector de arestas
	 * @param d destino da aresta
	 * @param w peso da aresta
	 * @param tw se é de 2 sentidos a estrada
	 * @param n nome da aresta
	 * @param id id da aresta
	 * @param block se esta bloqueada
	 */
	void addEdge(Vertex<T> *d, double w, bool tw, string n, T id, bool block);
	/**
	 * Retira uma aresta do vector de arestas
	 * @param d destino da aresta a retirar
	 * @return returna true se existe ou false caso contrario
	 */
	bool removeEdgeTo(Vertex<T> *d);
	/**
	 *
	 * @return returna o nome do vertice
	 */
	string getName() const;
	/**
	 * define o nome da aresta
	 * @param name nome que quero atribuir a aresta
	 */
	void setName(string name);
	/**
	 *
	 * @return returna a longitude do vertice
	 */
	double getLongitude() const;
	/**
	 *
	 * @return returna a latitude do vertice
	 */
	double getLatitude() const;
	/**
	 *
	 * @return returna a distancia do vertice
	 */
	double getDist() const;
	/**
	 *
	 * @return returna o proximo vertice do caminho
	 */
	Vertex<T> * getPath() const;
	/**
	 *
	 * @return returna a proxima aresta do caminho
	 */
	Edge<T> * getCaminho() const;
	friend class MutablePriorityQueue<Vertex<T>>;
	friend class Graph<T>;
};

template <class T>
Vertex<T>::Vertex(T in,string name, double lat, double lon): info(in), name(name), latitude(lat), longitude(lon) {}

template <class T>
T Vertex<T>::getInfo() const {
	return info;
}

template <class T>
vector<Edge<T>*> Vertex<T>::getAdj() const {
	return adj;
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}


/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w, bool tw, string n, T id, bool block) {
	adj.push_back(new Edge<T>(d, w, tw, n, id, block));
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	for (typename vector<Edge<T>>::iterator it = this->adj.begin();
			it != this->adj.end(); it++) {
		if (it->dest->info == d->info) {
			it = this->adj.erase(it);
			return true;
		}
	}
	return false;
}

template <class T>
string Vertex<T>::getName() const {
	return name;
}

template <class T>
void Vertex<T>::setName(string name) {
	this->name = name;
}

template <class T>
double Vertex<T>::getLongitude() const{
	return this->longitude;
}

template <class T>
double Vertex<T>::getLatitude() const{
	return this->latitude;
}

template <class T>
double Vertex<T>::getDist() const {
	return dist;
}

template<class T>
Vertex<T> * Vertex<T>::getPath() const {
	return this->path;
}

template<class T>
Edge<T> * Vertex<T>::getCaminho() const {
	return this->caminho;
}

template <class T>
struct vertex_greater_than {
    bool operator()(Vertex<T> * a, Vertex<T> * b) const {
        return a->getDist() > b->getDist();
    }
};





/*
 * ================================================================================================
 * Class Edge - Vias
 * ================================================================================================
 */
/*
 * Class que representa uma aresta do grafo
 */
template <class T>
class Edge {
	/**
	 * vertice de destino da aresta
	 */
	Vertex<T> * dest;
	/**
	 * peso da aresta
	 */
	double weight;
	/**
	 * nome da aresta
	 */
	string name;
	/**
	 * id da aresta
	 */
	T id;
	/**
	 * estado de bloqueio da aresta
	 */
	bool blocked;
	/**
	 * true caso a aresta seja de 2 sentidos
	 */
	bool two_ways;
	/**
	 * quantidade de carros na aresta
	 */
	int quantidade_carros;

public:
	/**
	 * Construtor da class Edge
	 * @param d destinho da aresta
	 * @param w peso da aresta
	 * @param tw se é uma aresta de 2 sentidos
	 * @param n nome da aresta
	 * @param id id da aresta
	 * @param block se a aresta esta bloqueada
	 */
	Edge(Vertex<T> *d, double w, bool tw, string n, T id, bool block);
	/**
	 *
	 * @return returna o id da aresta
	 */
	T getId() const;
	/**
	 *
	 * @return returna o destino da aresta
	 */
	Vertex<T>* getDest() const;
	/**
	 *
	 * @return returna se a aresta é de dois sentidos
	 */
	bool getTwoWays() const;
	/**
	 *
	 * @return returna o peso da aresta
	 */
	double getWeight() const;
	/**
	 *
	 * @return returna o nome da aresta
	 */
	string getName() const;
	/**
	 *
	 * @return returna true caso a aresta esteja bloqueada ou false caso contrario
	 */
	bool getBlocked() const;
	/**
	 *
	 * @return returna a quantidade de carros que estão na aresta
	 */
	int getQuantidade() const;
	/**
	 * Define se a aresta esta bloqueada ou não
	 * @param blocked true se quero que a aresta esteja bloqueada ou false caso contrario
	 */
	void setBlocked(bool blocked);
	/**
	 * Overload do operador == para comparar 2 arestas
	 * @param edge segunda aresta que quero comparar
	 * @return returna true caso 2 id sejam iguais ou false caso contrario
	 */
	bool operator==(Edge<T> & edge) const;

	friend class Graph<T>;
	friend class Vertex<T>;

};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, bool tw, string n, T id, bool block) {
	this->id = id;
	this->dest = d;
	this->weight = w;
	this->two_ways = tw;
	this->name = n;
	this->blocked = block;
	this->quantidade_carros=0;
}

template <class T>
T Edge<T>::getId() const{
	return id;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const{
	return dest;
}

template <class T>
bool Edge<T>::getTwoWays() const{
	return two_ways;
}

template <class T>
double Edge<T>::getWeight() const{
	return weight;
}

template <class T>
string Edge<T>::getName() const{
	return name;
}

template <class T>
bool Edge<T>::getBlocked() const{
	return blocked;
}
template <class T>
int Edge<T>::getQuantidade() const{
	return quantidade_carros;
}

template <class T>
void Edge<T>::setBlocked(bool blocked) {
	this->blocked = blocked;
}

template <class T>
bool Edge<T>::operator==(Edge<T> & edge) const
{
	return this->id== edge.id;
}

/*
 * ================================================================================================
 * Class Graph
 * ================================================================================================
 */
/**
 * Class que trata das funcionalidades do grafo. Representa um grafo
 */
template <class T>
class Graph {
	/**
	 * Vector com os vertices do grafo
	 */
	vector<Vertex<T> *> vertexSet;
	/**
	 * vetor com os carros do grafo
	 */
	vector<Carro<T>*> carros;
	/**
	 * função auxiliar para a pesquisa em profundidade
	 * @param v vetor de ids
	 * @param res resultado
	 */
	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	/**
	 * função auxiliar para a pesquisa em profundidade
	 * @param v vetor de ids
	 * @param name nome da aresta
	 * @param blocked estado a mudar
	 */
	void dfsVisitSetEdgeBlocked(Vertex<T> *v, const string &name ,const  bool & blocked);
	/**
	 * Função que procura o vertice do grafo
	 * @param in id do vertice
	 * @return vertice que esta a ser procurado ou null caso contrario
	 */
	Vertex<T> *findVertex(const T &in) const;
public:
	/**
	 *
	 * @return returna o vector de vertices da grafo
	 */
	vector<Vertex<T> *> getVertexSet() const;
	/**
	 * Returna o index de um vertice
	 * @param v id do vertice que quero encontrar
	 * @return returna o index do vertice no vector de vertices ou -1 caso não exista
	 */
	int getIndex(const T &v) const;
	/**
	 *
	 * @return returna o numero de vertices do grafo
	 */
	int getNumVertex() const;
	/**
	 * Returna o vertice com um certo id
	 * @param v id do vertice que pretendo procurar
	 * @return o vertice que estou a procurar o NULL caso contrario
	 */
	Vertex<T>* getVertex(const T &v) const;
	/**
	 * Returna o caminho mais curto apartir das arestas, adiciona a quantidade de carros nas arestas do caminho
	 * @param vec vector de vertices que contem o caminho mais curto
	 * @return returna um vector com as edges do percurso
	 */
	vector<Edge<T>*> getPathEdge(vector<Vertex<T>*> vec);
	/**
	 * Adiciona um vertice novo ao grafo
	 * @param in id do vertice
	 * @param name nome do vertice
	 * @param lon longitude do vertice
	 * @param lat latitude do vertice
	 * @return true caso consiga adicionar, false caso contrario/ ja existe
	 */
	bool addVertex(const T &in,string name, double lon, double lat);
	/**
	 * Remove um vertice do grafo
	 * @param in id do vertice
	 * @return true caso exista e removido ou false caso não exista
	 */
	bool removeVertex(const T &in);
	/**
	 * Adiciona uma aresta nova a um vertice
	 * @param sourc id de inicio da aresta
	 * @param dest id de destino da aresta
	 * @param w peso da aresta
	 * @param tw se a aresta é de 2 sentidos
	 * @param n nome da aresta
	 * @param id id da aresta
	 * @param block estado de bloqueio da aresta
	 * @return true caso consigo adicionar ou false caso contrario
	 */
	bool addEdge(const T &sourc, const T &dest, double w, bool tw, string n, T id, bool block);
	/**
	 * Remove uma aresta do grafo
	 * @param sourc id de inicio da aresta
	 * @param dest id de destino da aresta
	 * @return true caso exista e retire ou false caso não exista
	 */
	bool removeEdge(const T &sourc, const T &dest);
	/**
	 * Faz uma pesquisa de profundidade no garfo apartir do primeiro vertice
	 * @return um vetor com a pesquisa de profundidade
	 */
	vector<T> dfs() const;
	/**
	 * Faz um pesquisa de profundidade para procurar a aresta a bloquear
	 * @param name nome da aresta
	 * @param blocked estado para o qual quero mudar
	 */
	void dfsSetEdgeBlocked(const string &name ,const bool blocked);
	/**
	 * Faz uma pesquisa em largura no grafo
	 * @param source vertice de inicio
	 * @return o vector com a pesquisa em largura
	 */
	vector<T> bfs(const T &source) const;
	/**
	 * Faz uma organização topologica do grafo
	 * @return returna um vetor com a organização topologica
	 */
	vector<T> topsort() const;
	/**
	 * Returna o estado da aresta. Procura a aresta atraves de uma pesquisa em largura
	 * @param name nome da aresta
	 * @return boolean com a o estado da aresta
	 */
	bool bfsEdgeBlocked(const string & name) const;
	/**
	 * Calcula a dista entre dois vertice atraves do algoritmo de haversine
	 * @param id1 id do primeiro vertice
	 * @param id2 id do segundo vertice
	 * @return
	 */
	double calculateDist(T id1, T id2) const;
	/**
	 *
	 * @return returna o nome das aresta do grafo
	 */
	set<string> getEdgesNames() const;
	/**
	 *
	 * @return returna um vertor com as arestas do grafo
	 */
	vector<Edge<T> *> getEdges();
	/**
	 * Define uma aresta como bloqueada
	 * @param v id da aresta
	 * @param b estado para o qual quero mudar
	 */
	void setEdgeBlocked(const T &v, bool b);
	/**
	 * returna o caminho mais curto
	 * @param origin id de origem
	 * @param dest id de destino
	 * @return vetor com os id do caminho mais curto
	 */
	vector<T> getPath(const T &origin, const T &dest);
	/**
	 * Returna o caminho mais curto
	 * @param origin id de origem
	 * @param dest id de destino
	 * @return vector com os vertices do caminho mais curto
	 */
	vector<Vertex<T>*> getPathVertex(const T &origin, const T &dest);
	/**
	 * Faz o algoritmo de caminho mais curto sem ter em conta as distancias entre cada vertice
	 * @param s id de origem
	 */
	void unweightedShortestPath(const T &s);
	/**
	 * Algoritmo de caminho mais curto para grafos pesados
	 * @param s id de origem
	 */
	void dijkstraShortestPath(const T &s);
	/**
	 * Adiciona um carro novo ao grafo calculando o seu percurso no grafo
	 * @param inicio id de inicio do carro
	 * @param fim id de fim do carro
	 * @param id id do carro
	 */
	void addCar(const T &inicio,const T &fim,const T &id);
	/**
	 *
	 * @return returna o vector com todos os carros do grafo
	 */
	vector<Carro<T>*> getCarros() const { return this->carros;}
	/**
	 * Remove um carro do grafo
	 * @param id id do carro
	 * @return true caso removeu ou false caso contrario
	 */
	bool removeCar(int id);
	friend class Carro<T>;

	/**
	 * Apaga todos os vetores
	 */
	void eraseAll();
	friend class Carro<T>;
};

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
int Graph<T>::getIndex(const T &v) const{
	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
		if(this->vertexSet[i]->info == v)
			return i;

	return -1;
}

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet.at(i)->info == v) return vertexSet.at(i);
	return NULL;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in,string name, double lon, double lat) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in, name, lon, lat));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, bool tw, string n, T id, bool block) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2, w, tw, n, id, block);
	return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	Vertex<T> *de = this->findVertex(sourc), *para = this->findVertex(dest);
	if (de != NULL && para != NULL) {
		if (de->removeEdgeTo(para)) {
			return true;
		}
	}
	return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	Vertex<T> *apagar=this->findVertex(in);
		if(apagar==NULL)
			return false;
		typename vector<Vertex<T> *>::iterator guardar;
		for(typename vector<Vertex<T> *>::iterator it=this->vertexSet.begin();it!=this->vertexSet.end();it++)
		{
			this->removeEdge((*it)->info,apagar->info);
			if(*it==apagar)
			{
				guardar=it;
			}
		}
		this->vertexSet.erase(guardar);
		return true;
}

template<class T>
void Graph<T>::dfsSetEdgeBlocked(const string &name ,const bool blocked) {
	for (auto it : this->vertexSet) {
		it->visited = false;
	}
	for (auto it : this->vertexSet) {
		if (it->visited == false) {
			this->dfsVisitSetEdgeBlocked(it,name,blocked);
		}
	}
}
template<class T>
void Graph<T>::dfsVisitSetEdgeBlocked(Vertex<T> *v, const string &name ,const  bool & blocked) {
	v->visited = true;
	for (auto it : v->adj) {
		if(it->name==name)
		{
			it->blocked=blocked;
		}
		if (it->dest->visited == false) {
			this->dfsVisitSetEdgeBlocked(it->dest, name,blocked);
		}
	}
}

template <class T>
bool Graph<T>::bfsEdgeBlocked(const string & name) const {
	for (auto it : this->vertexSet) {
		it->visited = false;
	}
	queue<Vertex<T>*> fila;
	Vertex<T> *vertice = this->findVertex(1);
	fila.push(vertice);
	vertice->visited = true;
	while (!fila.empty()) {
		vertice = fila.front();
		fila.pop();

		for (auto it : vertice->adj) {
			if(it->name==name)
			{
				return it->blocked;
			}
			if (it->dest->visited == false) {
				fila.push(it->dest);
				it->dest->visited = true;
			}
		}
	}
	return false;
}

template <class T>
double Graph<T>::calculateDist(T id1, T id2) const{
	Vertex<T> *v1 = findVertex(id1);
	Vertex<T> *v2 = findVertex(id2);

	double R = 6371;

	double lat1r = v1->getLatitude() * M_PI / 180.0;
	double lat2r = v2->getLatitude() * M_PI / 180.0;
	double lon1r = v1->getLongitude() * M_PI / 180.0;
	double lon2r = v2->getLongitude() * M_PI / 180.0;

	double latdiff = abs(lat2r - lat1r);
	double londiff = abs(lon2r - lon1r);
	double u = sin(latdiff/2);
	double v = sin(londiff/2);

	return 2.0 * R * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));;
}

template <class T>
set<string> Graph<T>::getEdgesNames() const{
    set<string> edge_names;
    for(size_t i  = 0; i < vertexSet.size(); i++){
    	for(size_t n = 0; n < vertexSet.at(i)->getAdj().size(); n++){
    		edge_names.insert(vertexSet.at(i)->getAdj().at(n)->getName());
    	}
    }
    return edge_names;
}

template<class T>
void Graph<T>::setEdgeBlocked(const T &v, bool b) {
	for (auto ve : this->vertexSet) {
		for (auto w : ve->adj) {
			if (w->id == v) {
				w->blocked = b;
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) {
	auto inicio = this->findVertex(origin);
	auto fim = this->findVertex(dest);
	vector<T> res;
	if (inicio->dist != fim->dist) {
		if (fim->path != NULL) {
			res = this->getPath(origin, fim->path->info);
		} else {
			res.clear();
			return res;
		}
	}
	res = this->getPath(origin, fim->path->info);
	res.push_back(dest);
	return res;
}
template<class T>
vector<Vertex<T>*> Graph<T>::getPathVertex(const T &origin, const T &dest) {
	auto inicio = this->findVertex(origin);
	auto fim = this->findVertex(dest);
	vector<Vertex<T>*> res;
	if (inicio->dist != fim->dist) {
		if (fim->path != NULL) {
			res = this->getPathVertex(origin, fim->path->info);
		} else {
			res.clear();
			return res;
		}
	}
	res.push_back(fim);
	return res;
}

template <class T>
vector<Edge<T>*> Graph<T>::getPathEdge(vector<Vertex<T>*> vec)
{
	vector<Edge<T>*> res;
	for(auto v:vec)
	{
		if (v->caminho != NULL) {
			res.push_back(v->caminho);
			v->caminho->quantidade_carros++;
		}
	}
	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {
	for (auto it : this->vertexSet) {
		it->dist = INF;
		it->path=nullptr;
	}
	auto inicio=this->findVertex(s);
	inicio->dist=0;
	queue<Vertex<T>*>fila;
	fila.push(inicio);
	while(!fila.empty())
	{
		auto v=fila.front();
		fila.pop();
		for(auto w:v->adj)
		{
			if(w.dest->dist==INF)
			{
				fila.push(w.dest);
				w.dest->dist=v->dist+1;
				w.dest->path=v;
			}
		}
	}
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &s) {
	for (auto it : this->vertexSet) {
		it->dist = INF;
		it->path=nullptr;
		it->caminho=nullptr;
	}
	MutablePriorityQueue<Vertex<T>> fila;
	Vertex<T> *inicio=this->findVertex(s);
	inicio->dist=0;
	fila.insert(inicio);
	while(!fila.empty())
	{
		inicio=fila.extractMin();
		for(auto et:inicio->adj)
		{
			if(et->blocked== true || et->quantidade_carros >= MAX_CAPACITY){
				continue;
			}
			auto guardado=et->dest->dist;
			if(et->dest->dist>inicio->dist+et->weight)
			{
				et->dest->dist=inicio->dist+et->weight;
				et->dest->path=inicio;
				et->dest->caminho=et;

				if(guardado == INF)
				{
					fila.insert(et->dest);
				}
				else
				{
					fila.decreaseKey(et->dest);
				}
			}
		}
	}
}

template <class T>
void Graph<T>::addCar(const T &inicio,const T &fim , const T &id)
 {
	Carro<T>* novo = new Carro<T>(inicio, fim,id);
	this->dijkstraShortestPath(inicio);
	novo->nodes_path = this->getPathVertex(novo->id_inicio, novo->id_fim);
	if (novo->nodes_path.size() == 0) {
		novo->tem_percurso = false;
		this->carros.push_back(novo);
		return;
	}
	novo->edge_path = this->getPathEdge(novo->nodes_path);
	this->carros.push_back(novo);
}

template <class T>
vector<Edge<T> *> Graph<T>::getEdges(){
	vector<Edge<T> *> ret;
	set<int> repeated;
	for(auto i:this->vertexSet){
		for(auto n:i->getAdj()){
			if (n->id > 0) {
				if (repeated.insert(n->id).second == true) {
					ret.push_back(n);
				}
			}
		}
	}
	return ret;
}

template <class T>
bool Graph<T>::removeCar(int id){
	int n = 0;
	for(auto i: carros){
		if(i->getId() == id){
			this->carros.erase(carros.begin() + n);
			return true;
		}
		n++;
	}
	return false;
}

template <class T>
void Graph<T>::eraseAll(){
	this->carros.clear();
	this->vertexSet.clear();
}

#endif /* GRAPH_H_ */
