#include <iostream>
#include "../grafo.cpp"

using namespace std;

Grafo parser(vector<pair<int,int> > &viajes){
	int nodos;   cin >> nodos;
	int aristas; cin >> aristas;
	Grafo grafo(nodos); 
	for (int i = 0; i < aristas; i++){
		int nod1; cin >> nod1; nod1--;
		int nod2; cin >> nod2; nod2--;
		grafo.agregarArista(nod1,nod2);
	}

	int cantViajes; cin >> cantViajes;
	
	for (int i = 0; i < cantViajes; i++){
		pair<int,int> viaje;
		int v1; cin >> v1;v1--;
		int v2; cin >> v2;v2--;
		viaje.first = v1; viaje.second = v2;
		viajes.push_back(viaje); 
	}

	return grafo;
}