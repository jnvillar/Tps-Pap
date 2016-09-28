#include <iostream>
#include <vector>
#include <assert.h> 
#include <queue>
#include <stack>

using namespace std;
bool debug = false;

class Grafo{
	public:
		Grafo(int n){
			for (int i = 0; i < n; ++i){
				vector<int> vacia;				
				listaAdy.push_back(vacia);
			}
			cantidadNodos = n;
			cantidadAristas = 0;
		}

		 

		void agregarArista(int nod1, int nod2){
			listaAdy[nod1].push_back(nod2);
			cantidadAristas++;
			return;
		}

		int cantNodos(){
			return cantidadNodos;
		}

		int cantAristas(){
			return cantidadAristas;
		}

		vector<int> nodosAdyacentes(int nodo){
			return listaAdy[nodo];
		}

		void imprimirGrafo(){
			for(int i = 0; i< cantidadNodos; i++){
				cout << i << " -> ";
				for(int j = 0; j<listaAdy[i].size(); j++){
					cout << listaAdy[i][j] << "  ";
				}
				cout << endl;
			}
		}

		stack<int> bfsKosaraju(int nodo){
			stack<int> hijos;
			stack<int> ordenKosaraju;
			vector<bool> visitados(cantidadNodos,false);
			vector<int> nodosAlcanzables;
			bfsKosarajuRecursion(nodo,hijos,visitados,nodosAlcanzables,ordenKosaraju);
			return ordenKosaraju;
		}

		void bfsKosarajuRecursion(int nodo, stack<int> &hijos, vector<bool> &visitados, vector<int> &nodosAlcanzables, stack<int> &ordenKosaraju){
				
			if(debug) cout << nodo << " " << listaAdy[nodo].size() << endl;

			if(!visitados[nodo]){
				nodosAlcanzables.push_back(nodo);
				visitados[nodo] = true;
				for (int i = 0; i < listaAdy[nodo].size(); i++){
					hijos.push(listaAdy[nodo][i]);
				}

				for (int i = 0; i < hijos.size(); i++){
					int aux = hijos.top();hijos.pop();
					bfsKosarajuRecursion(aux,hijos,visitados,nodosAlcanzables,ordenKosaraju);					
				}

				ordenKosaraju.push(nodo);
			}
		}

		vector<int> bfs(int nodo){
			stack<int> hijos;
			vector<bool> visitados(cantidadNodos,false);
			vector<int> nodosAlcanzables;
			bfsRecursion(nodo,hijos,visitados,nodosAlcanzables);
			return nodosAlcanzables;
		}

		void bfsRecursion(int nodo, stack<int> &hijos, vector<bool> &visitados, vector<int> &nodosAlcanzables){
				
			if(debug) cout << nodo << " " << listaAdy[nodo].size() << endl;

			cout << "hola" << endl;

			if(!visitados[nodo]){
				nodosAlcanzables.push_back(nodo);
				visitados[nodo] = true;
				for (int i = 0; i < listaAdy[nodo].size(); i++){
					hijos.push(listaAdy[nodo][i]);
				}

				for (int i = 0; i < hijos.size(); i++){
					int aux = hijos.top();hijos.pop();
					bfsRecursion(aux,hijos,visitados,nodosAlcanzables);
				}
			}
		}

		vector<int> dfs(int nodo){
			queue<int> hijos;
			vector<bool> visitados(cantidadNodos,false);
			vector<int> nodosAlcanzables;
			dfsRecursion(nodo,hijos,visitados,nodosAlcanzables);
			return nodosAlcanzables;
		}

		void dfsRecursion(int nodo, queue<int> &hijos, vector<bool> &visitados, vector<int> &nodosAlcanzables){
				
			if(debug) cout << nodo << " " << listaAdy[nodo].size() << endl;

			if(!visitados[nodo]){
				nodosAlcanzables.push_back(nodo);
				visitados[nodo] = true;
				for (int i = 0; i < listaAdy[nodo].size(); i++){
					hijos.push(listaAdy[nodo][i]);
				}

				for (int i = 0; i < hijos.size(); i++){
					int aux = hijos.front();hijos.pop();
					dfsRecursion(aux,hijos,visitados,nodosAlcanzables);
				}
			}
		}



		void invertirAristas(){

			vector< vector<int> > aristasViejas = listaAdy;
			vector< vector<int> > vacio; listaAdy = vacio;

			for (int i = 0; i < cantidadNodos; i++){
				vector<int> vacio;
				listaAdy.push_back(vacio);
			}					
			
			for (int i = 0; i < aristasViejas.size(); i++){
				for (int j = 0; j < aristasViejas[i].size(); j++){
					agregarArista(aristasViejas[i][j],i);
				}
			}
		}

		void kosaraju(){

			vector<bool> visitados(cantidadNodos,false);
			stack<int> ordenKosaraju;

			for (int i = 0; i<visitados.size() && !visitados[i]; i++){
				vector<int> nodosAlcanzables;
				nodosAlcanzables = bfs(i);

				for (int j = 0; j < nodosAlcanzables.size(); j++){
					visitados[nodosAlcanzables[j]] = true;
				}

				for (int j = 0; j < nodosAlcanzables.size(); j++){
					ordenKosaraju.push(nodosAlcanzables[j]);
				}				
			}

		}

			
		

	private:
		vector< vector<int> > listaAdy;
		int cantidadNodos;
		int cantidadAristas;
};

