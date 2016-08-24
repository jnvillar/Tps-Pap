#include "p1.h"

/* Basicamente levanta los datos del standard input */
P1::P1(){
	unsigned int cantidad_packs;

	/* Entrada: standard input */
	cin >> this->presupuesto;
	cin >> cantidad_packs;
	/* ¿ Con listas esto será más rapido ? */
	this->primer_mitad_packs.resize( cantidad_packs/2 );
	this->segunda_mitad_packs.resize( cantidad_packs - cantidad_packs/2 );
	
	for ( unsigned int i = 0; i < this->primer_mitad_packs.size(); i++ ){
		cin >> this->primer_mitad_packs[i];
	}
	for ( unsigned int i = 0; i < this->segunda_mitad_packs.size(); i++ ){
		cin >> this->segunda_mitad_packs[i];
	}
}

unsigned int P1::agregar_conjunto( vector< unsigned int >& vec, unsigned int mask ){
	unsigned int res = 0;
	for(unsigned int i = 0; i <= mask; i++){
		if ( ( (1<<i) & mask ) > 0 ) { // si este elemento esta en la mascara, esta en el subconjunto 
			res += vec[i];
		}
	}
	return res;
}

void P1::crear_conjunto_partes_de(vector< unsigned int >& vec, set<unsigned int>& partes_de_ordenado){
	list<unsigned int> conjunto_partes;

	unsigned int tamano_conj_partes = pow(2,vec.size());

	for( unsigned int mask = 0; mask < tamano_conj_partes; mask++ )
		conjunto_partes.push_back( agregar_conjunto( vec, mask ) );

	for( list<unsigned int>::iterator it = conjunto_partes.begin(), end = conjunto_partes.end(); it != end; it++ )
		partes_de_ordenado.insert(*it);
}

/* Recorro la primer mitad de forma ascendente y la segunda de forma descendente */
unsigned int P1::calcular_maxima_compra( set<unsigned int> mitad_1, set<unsigned int> mitad_2 ){
	unsigned int res = 0, sum;
	set<unsigned int>::iterator it_1 = mitad_1.begin(), it_1_end = mitad_1.end();
	set<unsigned int>::reverse_iterator rit_2 = mitad_2.rbegin(), rit_2_end = mitad_2.rend();

	while( it_1 != it_1_end && rit_2 != rit_2_end ){
		sum = *it_1 + *rit_2;
		if( sum > this->presupuesto ){
			rit_2++;
		} else{
			res = sum;
			it_1++;

			if( sum == this->presupuesto ) 
				it_1 = it_1_end; //No voy a conseguir algo mejor que presupuesto
		}
	}

	return res;
}

/* Parto en dos y armo conjunto de partes 
	Los inserto en un set (futuro probar con arreglo/heap ).*/
unsigned int P1::resolver(){
	unsigned int res = 0;

	set<unsigned int> mitad_1,mitad_2;

	crear_conjunto_partes_de( primer_mitad_packs, mitad_1);
	
	crear_conjunto_partes_de( segunda_mitad_packs, mitad_2);

	res = calcular_maxima_compra( mitad_1, mitad_2);

	return res;
}