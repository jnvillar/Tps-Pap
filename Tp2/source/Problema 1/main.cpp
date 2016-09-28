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
			}
		}
	}

	vector<int> camino;
	int nodo = nodoFinal;
	camino.push_back(nodo);
	while(nodo != padre[nodo]){
		nodo = padre[nodo];
		camino.push_back(nodo);
	}

	reverse(camino.begin(),camino.end());
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
for (int i = 0; i < caminoAumento.size(); ++i)
{
	cout << caminoAumento[i] << "  ";
}
cout << endl;
		int maxAumento = 10000;
		for(int i = 0; i<caminoAumento.size()-1; i++){
			int a = caminoAumento[i];
			int b = caminoAumento[i+1];
			maxAumento = min(maxAumento,capacidad[a][b]-funcFlujo[a][b]);
		}
		for(int i = 0; i<caminoAumento.size()-1; i++){
			int a = caminoAumento[i];
			int b = caminoAumento[i+1];
			capacidad[a][b] += maxAumento;
		}
	}
	int res = 0;
	for(int i = 0; i<graph.cantNodos(); i++){
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
	Grafo graph(2*n+2);			// n_in en posiciones pares, n_out en impares, nodo n = s, nodo n+1 = t
	int cantNodos = 2*n+2;
	
	for(int i = 0; i<cantNodos; i+=2){
		graph.agregarArista(i,i+1);
	}
	for(int i = 0; i<m; i++){
		int desde,hasta;
		cin >> desde;
		cin >> hasta;
		desde--;
		hasta--;
		graph.agregarArista(2*desde+1,2*hasta);
		graph.agregarArista(2*hasta+1,2*desde);
	}
	for(int i = 0; i<alumnos.size(); i++){
		graph.agregarArista(n,2*alumnos[i]);
	}
	for(int i = 0; i<escuelas.size(); i++){
		graph.agregarArista(2*escuelas[i]+1,n+1);
	}

	vector<int> ceros(cantNodos,0);
	vector< vector<int> > capacidad(cantNodos,ceros);
	for(int i = 0; i<cantNodos; i++){
		vector<int> vecinos = graph.nodosAdyacentes(i);
		for(int j = 0; j<vecinos.size(); j++){
			capacidad[i][vecinos[j]] = 1;
		}
	}

	int res = flujoMaximo(graph,n,n+1,capacidad);
	cout << res << endl;
	return 0;
}

