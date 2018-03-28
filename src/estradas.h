//#ifndef SRC_ESTRADAS_H_
//#define SRC_ESTRADAS_H_
//
//#include <vector>
//#include <queue>
//#include <list>
//#include <limits>
//#include <cmath>
//
//using namespace std;
//
//#define INF std::numeric_limits<double>::max()
//
//template <class T> class Intercecao;
//template <class T> class Rua;
//template <class T> class Estradas;
////-----------------------------------Class Intercecao----------------------------------------------
//template <class T>
//class Intercecao
//{
//private:
//	T nome;
//	vector<Rua<T> > ruas_a_sair;
//	bool visitado;
//
//
//	void addRua(Intercecao<T> * destino,const T &nome, double weight);
//
//public:
//	Intercecao<T>(T nome);
//
//
//	friend class Estradas<T>;
//
//};
//template <class T>
//Intercecao<T>::Intercecao(T nome):nome(nome)
//{
//	this->visitado=false;
//}
//
////--------------------------------------Class Rua--------------------------------------------------
//template <class T>
//class Rua{
//private:
//	T nome;
//	Intercecao<T> *destino;
//	double weight;
//
//
//public:
//
//	Rua<T>(T nome,Intercecao<T> *destino, double weight);
//
//
//
//	friend class Estradas<T>;
//	friend class Intercecao<T>;
//};
//template<class T>
//Rua<T>::Rua(T nome,Intercecao<T> *destino, double weight):nome(nome),weight(weight)
//{
//	this->destino=destino;
//}
//
////---------------------------------------Class Estradas--------------------------------------------------
//template <class T>
//class Estradas
//{
//private:
//	vector<Intercecao<T>*> setEstradas;
//
//
//
//public:
//	Intercecao<T> * findIntercecao(const T &nome) const;
//	bool addIntercecao(const T &nome);
//	bool addRua(const T &de_onde, const T &para_onde, const T &nome,double weight);
//
//
//
//	friend class Rua<T>;
//};
//
//template<class T>
//Intercecao<T> * Estradas<T>::findIntercecao(const T &nome) const
//{
//	for(auto it: this->setEstradas)
//	{
//		if(it->nome==nome)
//		{
//			return it;
//		}
//	}
//	return NULL;
//}
//
//template<class T>
//bool Estradas<T>::addIntercecao(const T &nome)
//{
//	if(this->findIntercecao(nome) != NULL)
//	{
//		return false;
//	}
//	this->setEstradas.push_back(Intercecao<T>(nome));
//	return true;
//}
//
//template<class T>
//bool Estradas<T>::addRua(const T &de_onde, const T &para_onde, const T &nome,double weight)
//{
//	Intercecao<T> *inter1=this->findIntercecao(de_onde),*inter2=this->findIntercecao(para_onde);
//	if(inter1==NULL || inter2 == NULL)
//	{
//		return false;
//	}
//	inter2->addRua(inter2,nome,weight);
//	return true;
//
//}
//
//template<class T>
//void Intercecao<T>::addRua(Intercecao<T> * destino,const T &nome, double weight)
//{
//	this->ruas_a_sair.push_back(Rua<T>(nome,destino,weight));
//}
//
//#endif /* SRC_ESTRADAS_H_ */
