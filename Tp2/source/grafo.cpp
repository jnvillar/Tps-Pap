#include <iostream>
#include <vector>
#include <assert.h> 

using namespace std;




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
	private:
		vector< vector<int> > listaAdy;
		int cantidadNodos;
		int cantidadAristas;
};