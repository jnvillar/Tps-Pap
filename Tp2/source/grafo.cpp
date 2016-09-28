#include <iostream>
#include <vector>
#include <assert.h> 
#include <queue>

using namespace std;
bool debug = true;

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

		vector<int> dfs(int nodo){
			queue<int> hijos;
			vector<int> visitados(cantidadNodos,false);
			vector<int> nodosAlcanzables;
			dfsRecursion(nodo,hijos,visitados,nodosAlcanzables);
			return nodosAlcanzables;
		}

		void dfsRecursion(int nodo, queue<int> &hijos, vector<int> &visitados, vector<int> &nodosAlcanzables){
				
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

	private:
		vector< vector<int> > listaAdy;
		int cantidadNodos;
		int cantidadAristas;
};

