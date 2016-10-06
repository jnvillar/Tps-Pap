#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "grafo.cpp"

using namespace std;

vector<int> bfs(Grafo graph, int nodoInical, int nodoFinal, vector< vector<int> > capacidad, vector< vector<int> > funcFlujo){
	vector<bool> visitados(graph.cantNodos(),false);
	vector<int> padre(graph.cantNodos(),-1);		// aca me guardo el padre de cada nodo visitado, es decir, de que nodo vengo
	queue<int> cola;
	padre[nodoInical] = nodoInical;
	visitados[nodoInical] = true;
	cola.push(nodoInical);
	while(!cola.empty()){
		int nodo = cola.front();
		cola.pop();
		if (nodo == nodoFinal){		// si llegue a nodoFinal termino
			break;
		}
		vector<int> vecinos = graph.nodosAdyacentes(nodo);
		for(int i = 0; i<vecinos.size(); i++){
			if(!visitados[vecinos[i]] && capacidad[nodo][vecinos[i]]-funcFlujo[nodo][vecinos[i]]>0){	// si no fue visitado, y la red residual me permite utilizar esa arista
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


int main(){
	int m,n;
	cin >> n;
	cin >> m;
	vector<int> escuelas;
	vector<int> alumnos;
	for (int i = 0; i < n; i++){
		char val;
		cin >> val;
		if(val == 'E'){
			escuelas.push_back(i);
		} else if (val == 'A'){
			alumnos.push_back(i);
		}
	}
	Grafo graph(2*n+2);			// n_in en posiciones pares, n_out en impares, nodo cantNodos-2 = s, nodo cantNodos-2 = t
	int cantNodos = 2*n+2;
	
	for(int i = 0; i<cantNodos-2; i+=2){		// agregamos arista n_in -> n_out
		graph.agregarArista(i,i+1);
	}
	for(int i = 0; i<m; i++){ 		// para cada calle que conecta un par de esquinas a y b, agregamos una arista a_out -> b_in y b_out -> a_in
		int desde,hasta;
		cin >> desde;
		cin >> hasta;
		desde--;				// para que los nodos comienzen en 0
		hasta--;
		graph.agregarArista(2*desde+1,2*hasta);
		graph.agregarArista(2*hasta+1,2*desde);
	}
	for(int i = 0; i<alumnos.size(); i++){		// para cada nodo (esquina) que tiene un alumno, agregamos una arista s -> n_in
		graph.agregarArista(cantNodos-2,2*alumnos[i]);
	}
	for(int i = 0; i<escuelas.size(); i++){		// para cada nodo (esquina) que tiene una escuela, agregamos una arista n_out -> t 
		graph.agregarArista(2*escuelas[i]+1,cantNodos-1);
	}


	vector<int> ceros(cantNodos,0);
	vector< vector<int> > capacidad(cantNodos,ceros);
	for(int i = 0; i<cantNodos; i++){					// creamos la matriz que contiene la capacidad de cada arista (1 si existe la arista, 0 sino)
		vector<int> vecinos = graph.nodosAdyacentes(i);
		for(int j = 0; j<vecinos.size(); j++){
			capacidad[i][vecinos[j]] = 1;
		}
	}

	int res = flujoMaximo(graph,cantNodos-2,cantNodos-1,capacidad);
	cout << res << endl;
	return 0;
}

