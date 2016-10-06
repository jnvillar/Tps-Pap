#ifndef __P3_H_INCLUDED__
#define __P3_H_INCLUDED__
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

class EJ3{
	public:

		typedef struct t_calle{
			int desde;
			int hasta;

			t_calle(int a, int b):desde(a),hasta(b){};
			t_calle():desde(0),hasta(0){};
		} calle;

		/*Variables*/
		vector< int > depth, low, comp, c_nodos_comp ;
		int c_componentes;
		
		//Representamos el grafo con una lista de adyacencias
		vector< vector< int > > grafo;

		//Es necesario reconocer el numero de calle en la query B en O(1)		
		vector< calle > calles;

		EJ3();

		/*Queries*/
		int queryA(int , int );
		bool queryB(int );
		bool queryC(int );

	private:

		void init(int );

		int dfs( int v_actual, int actual_depth, int v_padre, stack<calle> &pila);
		void reportarComponenteBiconexa(stack<calle>&, calle );
		
		/*Consultas*/
		bool es_puente(int, int);
		int cant_en_comp_conexa(int esquina);
		int bfs( int, int );
};

#endif