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

		 void agregarNodo(){
		 	cantidadNodos++;
		 	vector<int> vacia;				
			listaAdy.push_back(vacia);
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

		stack<int> ordenKosaraju(){
			stack<int> res;
			vector<bool> visitados(cantidadNodos,false);

			for (int i = 0; i < visitados.size(); i++){
				if(!visitados[i]){
				stack<int> hijos;
				vector<int> ordenKosaraju;
					vector<int> nodosAlcanzables;
					bfsKosarajuRecursion(i,hijos,visitados,nodosAlcanzables,ordenKosaraju);
					for (int j = 0; j < ordenKosaraju.size(); j++){
						res.push(ordenKosaraju[j]);
					}								
				}
			}
			return res;
		}

		void bfsKosarajuRecursion(int nodo, stack<int> &hijos, vector<bool> &visitados, vector<int> &nodosAlcanzables, vector<int> &ordenKosaraju){
				
			if(debug) cout << nodo << " " << listaAdy[nodo].size() << endl;
			
			if(!visitados[nodo]){
				nodosAlcanzables.push_back(nodo);
				visitados[nodo] = true;
				for (int i = 0; i < listaAdy[nodo].size(); i++){
					hijos.push(listaAdy[nodo][i]);
				}

				while(!hijos.empty()){
					int aux = hijos.top();hijos.pop();
					bfsKosarajuRecursion(aux,hijos,visitados,nodosAlcanzables,ordenKosaraju);					
				}				
				ordenKosaraju.push_back(nodo);
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
		
			if(!visitados[nodo]){
				nodosAlcanzables.push_back(nodo);
				visitados[nodo] = true;
				for (int i = 0; i < listaAdy[nodo].size(); i++){
					hijos.push(listaAdy[nodo][i]);
				}

				while(!hijos.empty()){
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

				while(!hijos.empty()){
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

		vector<vector<int> > componentesConexas(stack<int> &ordenKosaraju){   //Esto devuelve los nodos que forman parte de una compoenente 
			vector<vector<int> > res;										  //en un vector de vectores. Saber si dos nodos perteneces a la 
			vector<bool> visitados(cantidadNodos,false);					  //misma componente es costoso, pero ver todos los nodos de una 
			while(!ordenKosaraju.empty()){									  //compoente conexa en mas eficiente.No se usa,pero puede servir 
				int nodo = ordenKosaraju.top(); ordenKosaraju.pop();
				if(!visitados[nodo]){
					vector<int> componenteConexa;
					vector<int> nodosAlcanzables = dfs(nodo);
					for (int i = 0; i < nodosAlcanzables.size(); i++){
						if(!visitados[nodosAlcanzables[i]]){
							visitados[nodosAlcanzables[i]] = true;
							componenteConexa.push_back(nodosAlcanzables[i]);
						}
					}
					res.push_back(componenteConexa);
				}				
			}
			return res;
		}

		vector<int> componentesKosaraju(stack<int> &ordenKosaraju){   //Esto devuelve un vector en el cual cada posicion es un nodo 
			vector<int> res(cantidadNodos,-1);						  //y su contenido es la componente conexa a la que pertenece 
			int componenteConexa = -1;								  //de esta manera dados dos nodos podemos saber en O(1) 
			vector<bool> visitados(cantidadNodos,false);			  //si pertenecen a la misma componente
			while(!ordenKosaraju.empty()){	
				int nodo = ordenKosaraju.top(); ordenKosaraju.pop();
				if(!visitados[nodo]){
					componenteConexa++;
					vector<int> nodosAlcanzables = dfs(nodo);
					for (int i = 0; i < nodosAlcanzables.size(); i++){
						if(!visitados[nodosAlcanzables[i]]){
							visitados[nodosAlcanzables[i]] = true;
							res[nodosAlcanzables[i]] = componenteConexa;
						}
					}					
				}				
			}
			return res;
		}


		vector<vector<int> > kosaraju2(){			
			stack<int> ordKosaraju = ordenKosaraju();
			invertirAristas();
			vector<vector<int> > compConex = componentesConexas(ordKosaraju);
			return compConex;
		}

		vector<int> kosaraju(){			
			stack<int> ordKosaraju = ordenKosaraju();
			invertirAristas();
			vector<int> compConex = componentesKosaraju(ordKosaraju);
			return compConex;
		}

	private:
		vector< vector<int> > listaAdy;
		int cantidadNodos;
		int cantidadAristas;
};

