#ifndef __P1_H_INCLUDED__
#define __P1_H_INCLUDED__
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

class P1{

	private:
		unsigned int presupuesto;
		vector< unsigned int > primer_mitad_packs; 
		vector< unsigned int > segunda_mitad_packs;

		unsigned int calcular_maxima_compra( vector<unsigned int>&, vector<unsigned int>& );
		unsigned int sumar_elementos_subconjunto( vector< unsigned int >&, unsigned int );
		void crear_conjunto_partes_de( vector<unsigned int>&, vector<unsigned int>& );

	public:
		P1();
		unsigned int resolver();
};

#endif