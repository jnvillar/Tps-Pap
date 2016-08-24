#ifndef __P1_H_INCLUDED__
#define __P1_H_INCLUDED__
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <list>

using namespace std;

class P1{

	private:
		unsigned int presupuesto;
		vector< unsigned int > primer_mitad_packs; 
		vector< unsigned int > segunda_mitad_packs;

		unsigned int calcular_maxima_compra( set<unsigned int>, set<unsigned int>);
		unsigned int agregar_conjunto( vector< unsigned int >&, unsigned int);
		void crear_conjunto_partes_de( vector<unsigned int>&, set<unsigned int>&);

	public:
		P1();
		unsigned int resolver();
};

#endif