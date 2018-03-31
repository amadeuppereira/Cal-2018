/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <string>
#include <math.h>
#include <set>
#include <list>
#include <limits>
#include <climits>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()
const int INT_INFINITY = INT_MAX;

/*
 * ================================================================================================
 * Class Vertex - Interseções
 * ================================================================================================
 */

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	bool processing;       // auxiliary field used by isDAG
	int indegree;          // auxiliary field used by topsort

	string name;
	double latitude;
	double longitude;
	double dist = 0;
	Vertex<T> *path = NULL;

public:
	Vertex(T in, double lon, double lat);
	friend class Graph<T>;

	T getInfo() const;
	vector<Edge<T> > getAdj() const;
	void addEdge(Vertex<T> *d, double w, bool tw, string n, T id, bool block);
	bool removeEdgeTo(Vertex<T> *d);

	string getName() const;
	void setName(string name);
	double getLongitude() const;
	double getLatitude() const;
};

template <class T>
Vertex<T>::Vertex(T in, double lat, double lon): info(in), latitude(lat), longitude(lon) {}

template <class T>
T Vertex<T>::getInfo() const {
	return info;
}

template <class T>
vector<Edge<T> > Vertex<T>::getAdj() const {
	return adj;
}


/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w, bool tw, string n, T id, bool block) {
	adj.push_back(Edge<T>(d, w, tw, n, id, block));
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	for (auto it = adj.begin(); it != adj.end(); it++)
		if (it->dest  == d) {
			adj.erase(it);
			return true;
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
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, bool tw, string n, T id, bool block): dest(d), weight(w), two_ways(tw), id(id), name(n), blocked(block) {}

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




/*
 * ================================================================================================
 * Class Graph
 * ================================================================================================
 */

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;

	int ** W;   //weight
	int ** P;   //path
public:
	vector<Vertex<T> *> getVertexSet() const;
	int getIndex(const T &v) const;
	int getNumVertex() const;
	Vertex<T>* getVertex(const T &v) const;
	bool addVertex(const T &in, double lon, double lat);
	bool removeVertex(const T &in);

	bool addEdge(const T &sourc, const T &dest, double w, bool tw, string n, T id, bool block);
	bool removeEdge(const T &sourc, const T &dest);

	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;

	int calculateDist(T id1, T id2) const;
	set<string> getEdgesNames() const;
	void setEdgeBlocked(const T &v, bool b);

	vector<T> getPath(const T &origin, const T &dest) const;
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);
	int edgeCost(int vOrigIndex, int vDestIndex);
	void floydWarshallShortestPath();
};

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
int Graph<T>::getIndex(const T &v) const{
	for (int i = 0; i < this->vertexSet.size(); i++)
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
		if (vertexSet[i]->info == v) return vertexSet[i];
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
bool Graph<T>::addVertex(const T &in, double lon, double lat) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in, lon, lat));
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
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeEdgeTo(v2);
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
		if ((*it)->info  == in) {
			auto v = *it;
			vertexSet.erase(it);
			for (auto u : vertexSet)
				u->removeEdgeTo(v);
			delete v;
			return true;
		}
	return false;
}

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	vector<T> res;
	for (auto v : vertexSet)
		v->visited = false;
	for (auto v : vertexSet)
	    if (! v->visited)
	    	dfsVisit(v, res);
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (auto & e : v->adj) {
		auto w = e.dest;
	    if ( ! w->visited)
	    	dfsVisit(w, res);
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
	auto s = findVertex(source);
	if (s == NULL)
		return res;
	queue<Vertex<T> *> q;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		res.push_back(v->info);
		for (auto & e : v->adj) {
			auto w = e.dest;
		    if ( ! w->visited ) {
				q.push(w);
				w->visited = true;
		    }
		}
	}
	return res;
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

	for (auto v : vertexSet)
		v->indegree = 0;
	for (auto v : vertexSet)
		for (auto & e : v->adj)
			e.dest->indegree++;

	queue<Vertex<T>*> q;
	for (auto v : vertexSet)
		if (v->indegree == 0)
			q.push(v);

	while( !q.empty() ) {
		Vertex<T>* v = q.front();
		q.pop();
		res.push_back(v->info);
		for(auto & e : v->adj) {
			auto w = e.dest;
			w->indegree--;
			if(w->indegree == 0)
				q.push(w);
		}
	}

	if ( res.size() != vertexSet.size() ) {
		//cout << "Ordenacao Impossivel!" << endl;
		res.clear();
		return res;
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

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	auto s = findVertex(source);
	if (s == NULL)
			return 0;
	queue<Vertex<T> *> q;
	int maxChildren = 0;
	inf = s->info;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		int nChildren=0;
		for (auto & e : v->adj) {
			auto w = e.dest;
			if ( ! w->visited ) {
				w->visited = true;
				q.push(w);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren = nChildren;
			inf = v->info;
		}
	}
	return maxChildren;
}

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
	for (auto v : vertexSet) {
		v->visited = false;
		v->processing = false;
	}
	for (auto v : vertexSet)
	    if (! v->visited)
	    	if ( ! dfsIsDAG(v) )
	    		return false;
	return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	v->visited = true;
	v->processing = true;
	for (auto & e : v->adj) {
		auto w = e.dest;
    	if (w->processing)
    		return false;
	    if (! w->visited)
	    	if (! dfsIsDAG(w))
	    		return false;
	}
	v->processing = false;
	return true;
}

template <class T>
int Graph<T>::calculateDist(T id1, T id2) const{
	Vertex<T> *v1 = findVertex(id1);
	Vertex<T> *v2 = findVertex(id2);

	double long1 = v1->getLongitude();
	double lat1 = v1->getLatitude();
	double long2 = v2->getLongitude();
	double lat2 = v2->getLatitude();

	double dist = sqrt(pow((long1 - long2), 2) + pow((lat1 - lat2), 2));

	return floor(dist * 1000);
}

template <class T>
set<string> Graph<T>::getEdgesNames() const{
    set<string> edge_names;
    for(size_t i  = 0; i < vertexSet.size(); i++){
    	for(size_t n = 0; n < vertexSet.at(i)->getAdj().size(); n++){
    		if(vertexSet.at(i)->getAdj().at(n).getName() != "")
    			edge_names.insert(vertexSet.at(i)->getAdj().at(n).getName());
    	}
    }
    return edge_names;
}

template<class T>
void Graph<T>::setEdgeBlocked(const T &v, bool b) {
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		for (unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			if (vertexSet[i]->adj[j].id == v)
				vertexSet[i]->adj[j].blocked = b;
		}
	}
}


template <class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {
	vector<T> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) // missing or disconnected
		return res;
	for (; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest){

	int originIndex = -1, destinationIndex = -1;

	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if(vertexSet[i]->info == origin)
			originIndex = i;
		if(vertexSet[i]->info == dest)
			destinationIndex = i;

		if(originIndex != -1 && destinationIndex != -1)
			break;
	}


	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if(W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if(P[originIndex][destinationIndex] != -1)
	{
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex,destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);


	return res;
}



template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2, vector<T> & res)
{
	if(P[index1][index2] != -1)
	{
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2],index2, res);
	}
}

template<class T>
int Graph<T>::edgeCost(int vOrigIndex, int vDestIndex)
{
	if(vertexSet.at(vOrigIndex) == vertexSet.at(vDestIndex))
		return 0;

	for(unsigned int i = 0; i < vertexSet.at(vOrigIndex)->adj.size(); i++)
	{
		if(vertexSet.at(vOrigIndex)->adj.at(i).dest == vertexSet.at(vDestIndex)){
			if(vertexSet.at(vOrigIndex)->adj.at(i).blocked)
				continue;
			else return vertexSet.at(vOrigIndex)->adj.at(i).weight;
		}
	}

	return INT_INFINITY;
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new int * [vertexSet.size()];
	P = new int * [vertexSet.size()];
	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		W[i] = new int[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for(unsigned int j = 0; j < vertexSet.size(); j++)
		{
			W[i][j] = edgeCost(i,j);
			P[i][j] = -1;
		}
	}


	for(unsigned int k = 0; k < vertexSet.size(); k++)
		for(unsigned int i = 0; i < vertexSet.size(); i++)
			for(unsigned int j = 0; j < vertexSet.size(); j++)
			{
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem convém considerar essa soma
				if(W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				int val = min ( W[i][j], W[i][k]+W[k][j] );
				if(val != W[i][j])
				{
					W[i][j] = val;
					P[i][j] = k;
				}
			}

}

#endif /* GRAPH_H_ */
