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
#define MAX_CAPACITY 10


/*
 * ================================================================================================
 * Class Carro
 * ================================================================================================
 */
template <class T>
class Carro {
	T id;
	T id_inicio;
	T id_fim;
	vector<Vertex<T>*> nodes_path;
	vector<Edge<T>*> edge_path;
	bool tem_percurso=true;
public:
	Carro(T id_inicio,T id_fim,T id);

	const vector<Edge<T> *>& getEdgePath() const {
		return edge_path;
	}

	void setEdgePath(const vector<Edge<T> *>& edgePath) {
		edge_path = edgePath;
	}

	T getIdFim() const {
		return id_fim;
	}

	void setIdFim(T idFim) {
		id_fim = idFim;
	}

	T getIdInicio() const {
		return id_inicio;
	}

	void setIdInicio(T idInicio) {
		id_inicio = idInicio;
	}

	const vector<Vertex<T> *>& getNodesPath() const {
		return nodes_path;
	}

	void setNodesPath(const vector<Vertex<T> *>& nodesPath) {
		nodes_path = nodesPath;
	}

	bool isTemPercurso() const {
		return tem_percurso;
	}

	void setTemPercurso(bool temPercurso = true) {
		tem_percurso = temPercurso;
	}

	T getId() const {
		return id;
	}

	void setId(T id) {
		this->id = id;
	}
};

template<class T>
Carro<T>::Carro(T id_inicio, T id_fim, T id) :
		id_inicio(id_inicio), id_fim(id_fim), id(id) {

}



/*
 * ================================================================================================
 * Class Vertex - Interseções
 * ================================================================================================
 */

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T>*> adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	bool processing;       // auxiliary field used by isDAG
	int indegree;          // auxiliary field used by topsort

	string name;
	double latitude;
	double longitude;
	double dist = 0;

	Vertex<T> *path = NULL;
	Edge<T> *caminho = NULL;
	int queueIndex = 0;
public:
	Vertex(T in, string name, double lon, double lat);
	friend class Graph<T>;

	bool operator<(Vertex<T> & vertex) const;

	T getInfo() const;
	vector<Edge<T>*> getAdj() const;
	void addEdge(Vertex<T> *d, double w, bool tw, string n, T id, bool block);
	bool removeEdgeTo(Vertex<T> *d);

	string getName() const;
	void setName(string name);
	double getLongitude() const;
	double getLatitude() const;
	double getDist() const;
	Vertex<T> * getPath() const;
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

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight - Distância, tempos...

	string name;
	T id;
	bool blocked;
	bool two_ways;

	int quantidade_carros=0;

public:
	Edge(Vertex<T> *d, double w, bool tw, string n, T id, bool block);

	friend class Graph<T>;
	friend class Vertex<T>;

	T getId() const;
	Vertex<T>* getDest() const;
	bool getTwoWays() const;
	double getWeight() const;
	string getName() const;
	bool getBlocked() const;


	void setBlocked(bool blocked);

	bool operator==(Edge<T> & edge) const;

};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, bool tw, string n, T id, bool block) {
	this->id = id;
	this->dest = d;
	this->weight = w;
	this->two_ways = tw;
	this->name = n;
	this->blocked = block;
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

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	vector<Carro<T>*> carros;

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	void dfsVisitSetEdgeBlocked(Vertex<T> *v, const string &name ,const  bool & blocked);
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	vector<Vertex<T> *> getVertexSet() const;
	int getIndex(const T &v) const;
	int getNumVertex() const;
	Vertex<T>* getVertex(const T &v) const;
	vector<Edge<T>*> getPathEdge(vector<Vertex<T>*> vec);
	bool addVertex(const T &in,string name, double lon, double lat);
	bool removeVertex(const T &in);

	bool addEdge(const T &sourc, const T &dest, double w, bool tw, string n, T id, bool block);
	bool removeEdge(const T &sourc, const T &dest);

	vector<T> dfs() const;
	void dfsSetEdgeBlocked(const string &name ,const bool blocked);
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	bool bfsEdgeBlocked(const string & name) const;
	//int maxNewChildren(const T &source, T &inf) const;
	//bool isDAG() const;

	double calculateDist(T id1, T id2) const;
	set<string> getEdgesNames() const;
	bool setEdgeBlocked(const T &v, bool b);

	vector<T> getPath(const T &origin, const T &dest);
	vector<Vertex<T>*> getPathVertex(const T &origin, const T &dest);
	void unweightedShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);

	void setAllCarPath();
	void addCar(const T &inicio,const T &fim,const T &id);
	vector<Carro<T>*> getCarro() const { return this->carros;}

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

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::dfs() const {
	vector<T> res;
	for (auto it : this->vertexSet) {
		it->visited = false;
	}
	for (auto it : this->vertexSet) {
		if (it->visited == false) {
			this->dfsVisit(it, res);
		}
	}
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (auto it : v->adj) {
		if (it->dest->visited == false) {
			this->dfsVisit(it->dest, res);
		}
	}
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

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	vector<T> res;
	for (auto it : this->vertexSet) {
		it->visited = false;
	}
	queue<Vertex<T>*> fila;
	Vertex<T> *vertice = this->findVertex(source);
	fila.push(vertice);
	vertice->visited = true;
	while (!fila.empty()) {
		vertice = fila.front();
		fila.pop();
		res.push_back(vertice->info);
		for (auto it : vertice->adj) {
			if (it->dest->visited == false) {
				fila.push(it->dest);
				it->dest->visited = true;
			}
		}
	}
	return res;
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

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::topsort() const {
	vector<T> res;
	for (auto it : this->vertexSet) {
		it->indegree = 0;
	}
	for (auto it : this->vertexSet) {
		for (auto et : it->adj) {
			et.dest->indegree++;
		}
	}

	queue<Vertex<T>*> fila;
	for (auto it : this->vertexSet) {
		if (it->indegree == 0) {
			fila.push(it);
		}
	}

	while (!fila.empty()) {
		Vertex<T>* v = fila.front();
		fila.pop();
		res.push_back(v->info);
		for (auto et : v->adj) {
			et.dest->indegree--;
			if (et.dest->indegree == 0) {
				fila.push(et.dest);
			}
		}
	}
	if (res.size() != this->vertexSet.size()) {
		res.clear();
	}
	return res;
}

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex and the number of new children.
 */

//template <class T>
//int Graph<T>::maxNewChildren(const T & source, T &inf) const {
//	auto s = findVertex(source);
//	if (s == NULL)
//			return 0;
//	queue<Vertex<T> *> q;
//	int maxChildren = 0;
//	inf = s->info;
//	for (auto v : vertexSet)
//		v->visited = false;
//	q.push(s);
//	s->visited = true;
//	while (!q.empty()) {
//		auto v = q.front();
//		q.pop();
//		int nChildren=0;
//		for (auto & e : v->adj) {
//			auto w = e.dest;
//			if ( ! w->visited ) {
//				w->visited = true;
//				q.push(w);
//				nChildren++;
//			}
//		}
//		if (nChildren>maxChildren) {
//			maxChildren = nChildren;
//			inf = v->info;
//		}
//	}
//	return maxChildren;
//}
//
///*
// * Performs a depth-first search in a graph (this), to determine if the graph
// * is acyclic (acyclic directed graph or DAG).
// * During the search, a cycle is found if an edge connects to a vertex
// * that is being processed in the the stack of recursive calls (see theoretical classes).
// * Returns true if the graph is acyclic, and false otherwise.
// */
//
//template <class T>
//bool Graph<T>::isDAG() const {
//	for (auto v : vertexSet) {
//		v->visited = false;
//		v->processing = false;
//	}
//	for (auto v : vertexSet)
//	    if (! v->visited)
//	    	if ( ! dfsIsDAG(v) )
//	    		return false;
//	return true;
//}
//
///**
// * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
// * Returns false (not acyclic) if an edge to a vertex in the stack is found.
// */
//template <class T>
//bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
//	v->visited = true;
//	v->processing = true;
//	for (auto & e : v->adj) {
//		auto w = e.dest;
//    	if (w->processing)
//    		return false;
//	    if (! w->visited)
//	    	if (! dfsIsDAG(w))
//	    		return false;
//	}
//	v->processing = false;
//	return true;
//}*/

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
    		if(vertexSet.at(i)->getAdj().at(n)->getName() != "")
    			edge_names.insert(vertexSet.at(i)->getAdj().at(n)->getName());
    	}
    }
    return edge_names;
}

template<class T>
bool Graph<T>::setEdgeBlocked(const T &v, bool b) {
	for (auto ve : this->vertexSet) {
		for (auto w : ve->adj) {
			if (w->id == v) {
				w->blocked = b;
			}
		}
	}
	return true;
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
		res.push_back(v->caminho);
		v->caminho->quantidade_carros++;
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
			if(et->blocked== true || et->quantidade_carros==MAX_CAPACITY)
				continue;
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
void Graph<T>::setAllCarPath()
{
	for(auto it:this->carros)
	{
		this->dijkstraShortestPath(it->id_inicio);
		it->nodes_path=this->getPathVertex(it->id_inicio,it->id_fim);
		if(it->node_path.size()==0)
		{
			it->tem_percurso=false;
			return;
		}
		it->edge_path=this->getPathEdge(it->nodes_path);
	}
}

template <class T>
void Graph<T>::addCar(const T &inicio,const T &fim , const T &id)
 {
	Carro<T>* novo= new Carro<T>(inicio, fim,id);
	this->dijkstraShortestPath(inicio);
	novo->nodes_path = this->getPathVertex(novo->id_inicio, novo->id_fim);
	if (novo->node_path.size() == 0) {
		novo->tem_percurso = false;
		return;
	}
	novo->edge_path = this->getPathEdge(novo->nodes_path);
}


#endif /* GRAPH_H_ */
