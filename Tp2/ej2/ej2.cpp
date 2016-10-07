#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "grafo.cpp"

using namespace std;



vector<int> bfs(Grafo graph, int nodoInical, int nodoFinal, vector< vector<int> > capacidad, vector< vector<int> > funcFlujo){
	vector<bool> visitados(graph.cantNodos(),false);
	vector<int> padre(graph.cantNodos(),-1);			// aca me guardo el padre de cada nodo visitado, es decir, de que nodo vengo
	queue<int> cola;
	padre[nodoInical] = nodoInical;
	visitados[nodoInical] = true;
	cola.push(nodoInical);
	while(!cola.empty()){
		int nodo = cola.front();
		cola.pop();
		if (nodo == nodoFinal){			// si llegue a nodoFinal termino
			break;
		}
		vector<int> vecinos = graph.nodosAdyacentes(nodo);
		for(int i = 0; i<vecinos.size(); i++){
			if(!visitados[vecinos[i]] && capacidad[nodo][vecinos[i]]-funcFlujo[nodo][vecinos[i]]>0){		// si no fue visitado, y la red residual me permite utilizar esa arista
				cola.push(vecinos[i]);
				padre[vecinos[i]] = nodo;
				visitados[vecinos[i]] = true;
			}
		}
	}


	vector<int> camino;
	if(visitados[nodoFinal]){	// si llegue al nodoFinal
		int nodo = nodoFinal;	// reconstruyo el camino desde nodoInical a nodoFinal
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
	
	for(int i = 0; i<graph.cantNodos(); i++){	// transformo graph en su red residual
		vector<int> vecinos = graph.nodosAdyacentes(i);
		for(int j = 0; j<vecinos.size(); j++){
			graph.agregarArista(vecinos[j],i);
		}
	}

	vector<int> ceros(graph.cantNodos(),0);	
	vector< vector<int> > funcFlujo(graph.cantNodos(),ceros);	// empiezo con una funcion de flujo valida
	while(true){
		vector<int> caminoAumento = bfs(graph,s,t,capacidad,funcFlujo);		// busco camino de aumento
		if(caminoAumento.size() == 0){										// si no existe, termino. Encontre el flujo maximo
			break;
		}

		int maxAumento = 10000;
		for(int i = 0; i<caminoAumento.size()-1; i++){			// busco la maxima capacidad de flujo que puedo pasar por el camino de aumento
			int a = caminoAumento[i];
			int b = caminoAumento[i+1];
			maxAumento = min(maxAumento,capacidad[a][b]-funcFlujo[a][b]);
		}
		for(int i = 0; i<caminoAumento.size()-1; i++){			// actualizo la funcion de flujo
			int a = caminoAumento[i];
			int b = caminoAumento[i+1];
			funcFlujo[a][b] += maxAumento;
			funcFlujo[b][a] -= maxAumento;
		}
	}
	int res = 0;
	for(int i = 0; i<graph.cantNodos(); i++){		// el resultado es la cantidad de flujo que entra a t
		res += funcFlujo[i][t];
	}
	return res;
}


int matchingBipartito(Grafo graph, int cantNodosA, int cantNodosB){
	int s = cantNodosA+cantNodosB;
	int t = s+1;
	graph.agregarNodo();			// agrego al grafo a s
	graph.agregarNodo();			// agrego al grafo a t
	for(int i = 0; i<cantNodosA; i++){		// para todos los nodos de A, agrego una arista s -> i
		graph.agregarArista(s,i);
	}
	for(int i = 0; i<cantNodosB; i++){		// para todos los nodos de B, agrego una arista j -> t
		graph.agregarArista(cantNodosA+i,t);
	}
	
	vector<int> ceros(graph.cantNodos(),0);
	vector< vector<int> > capacidad(graph.cantNodos(),ceros);
	for(int i = 0; i<graph.cantNodos(); i++){				// creamos la matriz que contiene la capacidad de cada arista (1 si existe la arista, 0 sino)
		vector<int> vecinos = graph.nodosAdyacentes(i);
		for(int j = 0; j<vecinos.size(); j++){
			capacidad[i][vecinos[j]] = 1;
		}
	}


	int res = flujoMaximo(graph,s,t,capacidad);			// el matching maximo es igual al flujo maximo del grafo creado

	return res;

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

	Grafo graph(a);		// este grafo contendra un nodo por cada accion, y una arista i -> j si todos los dias, la accion i es menor a la accion j
	
	
	for(int i = 0; i<a; i++){
		for(int j = 0; j<a; j++){
			if(i != j){
				if (esMenor(acciones[i],acciones[j])){		// si todos los dias, la accion i es menor a la accion j
					graph.agregarArista(i,j);				// agrego una arista i -> j
				}
			}
		}
	}
	
	

	Grafo graphBipartite(2*a);		// creo el grafo bipartito
	for(int i = 0; i< graph.cantNodos(); i++){			// agrego una arista de i € A -> j € B si existe una arista i -> j en el grafo original
		vector<int> vecinos = graph.nodosAdyacentes(i);
		for(int j = 0; j<vecinos.size(); j++){
			graphBipartite.agregarArista(i,a+vecinos[j]);
		}
	}

	int res = a - matchingBipartito(graphBipartite,a,a); 		// res (la mayor anticadena = menor cubrimiento por caminos) es igual a la cantidad de nodos del grafo original - el matching maximo del grafo bipartito formado (Kőnig's theorem)
	cout << res << endl;
	return 0;
}

