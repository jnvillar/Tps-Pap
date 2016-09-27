#include <iostream>
#include <vector>
#include <assert.h> 

using namespace std;

class Nodo{
	public:
		Nodo(int n){
			numero = n;
			vector<Nodo*> misVecinos;
		}

		Nodo(int num, vector<Nodo*> misVecinos){
			numero = num;
			vecinos = misVecinos;
		}
		
		void agregarVecino(Nodo &vecinoNuevo){
			vecinos.push_back(&vecinoNuevo);
		}

		bool esVecinoDe(Nodo &nod){
			for (int i = 0; i < vecinos.size(); i++){
				if(vecinos[i]->getNumero() == nod.getNumero()){
					return true;
				}
			}
			return false;
		}

		int getNumero(){
			return numero;
		}

	private:
		vector<Nodo*> vecinos;
		int numero;
};


class Grafo{
	public:
		Grafo(vector<Nodo*> misNodos, int nods, int aris, bool tipo){
			esDirigido = tipo;
			nodos = misNodos;
			cantNodos = nods;
			cantAristas = aris;
		}

		Grafo(int nods, int aris, bool tipo){
			esDirigido = tipo;
			cantNodos = nods;
			cantAristas = aris;
		}

		void agregarAristaDirigida(int nod1, int nod2){
			assert(esDirigido);
			nodos[nod1]->agregarVecino(*nodos[nod2]);
			cantAristas++;
		}		 

		void agregarArista(int nod1, int nod2){
			assert(!esDirigido);
			nodos[nod1]->agregarVecino(*nodos[nod2]);
			nodos[nod2]->agregarVecino(*nodos[nod1]);
			cantAristas++;
		}

		void agregarNodo(Nodo &nuevoNodo){
			cantNodos++;
			nodos.push_back(&nuevoNodo);
		}

	private:
		bool esDirigido;
		vector<Nodo*> nodos;
		int cantNodos,cantAristas;
};