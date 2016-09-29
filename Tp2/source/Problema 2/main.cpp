#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "../grafo.cpp"

using namespace std;



vector<int> bfs(Grafo graph, int nodoInical, int nodoFinal, vector< vector<int> > capacidad, vector< vector<int> > funcFlujo){
	vector<bool> visitados(graph.cantNodos(),false);
	vector<int> padre(graph.cantNodos(),-1);
	queue<int> cola;
	padre[nodoInical] = nodoInical;
	visitados[nodoInical] = true;
	cola.push(nodoInical);
	while(!cola.empty()){
		int nodo = cola.front();
		cola.pop();
		if (nodo == nodoFinal){
			break;
		}
		vector<int> vecinos = graph.nodosAdyacentes(nodo);
		for(int i = 0; i<vecinos.size(); i++){
			if(!visitados[vecinos[i]] && capacidad[nodo][vecinos[i]]-funcFlujo[nodo][vecinos[i]]>0){
				cola.push(vecinos[i]);
				padre[vecinos[i]] = nodo;
				visitados[vecinos[i]] = true;
			}
		}
	}


	vector<int> camino;
	if(visitados[nodoFinal]){
		int nodo = nodoFinal;
		camino.push_back(nodo);
		while(nodo != padre[nodo]){
			nodo = padre[nodo];
			camino.push_back(nodo);
		}

		reverse(camino.begin(),camino.end());
	}

	return camino;
}

int flujoMaximo(Grafo graph, int s, int t, vector< vector<int> > capacidad){
	
	vector<int> ceros(graph.cantNodos(),0);
	vector< vector<int> > funcFlujo(graph.cantNodos(),ceros);
	while(true){
		vector<int> caminoAumento = bfs(graph,s,t,capacidad,funcFlujo);
		if(caminoAumento.size() == 0){
			break;
		}

		int maxAumento = 10000;
		for(int i = 0; i<caminoAumento.size()-1; i++){
			int a = caminoAumento[i];
			int b = caminoAumento[i+1];
			maxAumento = min(maxAumento,capacidad[a][b]-funcFlujo[a][b]);
		}
		for(int i = 0; i<caminoAumento.size()-1; i++){
			int a = caminoAumento[i];
			int b = caminoAumento[i+1];
			funcFlujo[a][b] += maxAumento;
		}
	}
	int res = 0;
	for(int i = 0; i<graph.cantNodos(); i++){
		res += funcFlujo[i][t];
	}
	return res;
}


int matchingBipartito(Grafo graph, int cantNodosA, int cantNodosB){
	int s = cantNodosA+cantNodosB;
	int t = s+1;
	graph.agregarNodo();
	graph.agregarNodo();
	for(int i = 0; i<cantNodosA; i++){
		graph.agregarArista(s,cantNodosA);
	}
	for(int i = 0; i<cantNodosB; i++){
		graph.agregarArista(cantNodosA+i,t);
	}
	
	vector<int> ceros(graph.cantNodos(),0);
	vector< vector<int> > capacidad(graph.cantNodos(),ceros);
	for(int i = 0; i<graph.cantNodos(); i++){
		vector<int> vecinos = graph.nodosAdyacentes(i);
		for(int j = 0; j<vecinos.size(); j++){
			capacidad[i][vecinos[j]] = 1;
		}
	}

	int res = flujoMaximo(graph,s,t,capacidad);

}


bool esMenor(vector<int> a, vector<int> b){
	for(int i = 0; i<a.size(); i++){
		if(a[i] >= b[i]){
			return false;
		}
	}
	return true;
}

int main(){
	int a,d;
	cin >> a;
	cin >> d;
	vector< vector<int> > acciones;
	for(int j = 0; j<a; j++){
		vector<int> accion;
		for (int i = 0; i < d; i++){
			int val;
			cin >> val;
			accion.push_back(val);
		}
		acciones.push_back(accion);
	}

	Grafo graph(a);
	vector<int> nodoIn(a,-1);
	vector<int> nodoOut(a,-1);
	int indiceIn = 0;
	int indiceOut = 0;
	
	for(int i = 0; i<a; i++){
		for(int j = 0; j<a; j++){
			if(i != j){
				if (esMenor(acciones[i],acciones[j])){
					graph.agregarArista(i,j);
					if(nodoIn[j]<0){
						nodoIn[j] = indiceIn;
						indiceIn++;
					}
					if(nodoOut[i]<0){
						nodoOut[i] = indiceOut;
						indiceOut++;
					}
				}
			}
		}
	}
	
	int cantNodosBipartitoA = 0;
	int cantNodosBipartitoB = 0;
	for(int i = 0; i<a; i++){
		if (nodoOut[i]>=0){
			cantNodosBipartitoA++;
		}
		if (nodoIn[i]>=0){
			cantNodosBipartitoB++;
		}
	}
	Grafo graphBipartite(cantNodosBipartitoA + cantNodosBipartitoB);
	for(int i = 0; i< graph.cantNodos(); i++){
		vector<int> vecinos = graph.nodosAdyacentes(i);
		for(int j = 0; j<vecinos.size(); j++){
			graphBipartite.agregarArista(nodoOut[i],cantNodosBipartitoA+nodoIn[vecinos[j]]);
		}
	}

	//graphBipartite.imprimirGrafo();
	int res = graph.cantNodos() - matchingBipartito(graphBipartite,cantNodosBipartitoA,cantNodosBipartitoB);
	cout << res << endl;
	return 0;
}

