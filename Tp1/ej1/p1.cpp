#include "p1.h"

/* Basicamente levanta los datos del standard input 

Complejidad: Lineal en cantidad_packs */
P1::P1(){
	unsigned int cantidad_packs;

	/* Entrada: standard input */
	cin >> this->presupuesto;
	cin >> cantidad_packs;
	

	this->primer_mitad_packs.resize( cantidad_packs/2 );
	this->segunda_mitad_packs.resize( cantidad_packs - cantidad_packs/2 );
	
	for ( unsigned int i = 0; i < this->primer_mitad_packs.size(); i++ )
		cin >> this->primer_mitad_packs[i];

	for ( unsigned int i = 0; i < this->segunda_mitad_packs.size(); i++ )
		cin >> this->segunda_mitad_packs[i];

}

/* Dada una mascara (@Param2) y un multiconjunto representado con un vector (@Param1), 
	se devuelve el resultado de sumar todos los elementos que formarían el subconjunto correspondiente a la máscara. 

Complejidad: Lineal en |@Param1| */
unsigned int P1::sumar_elementos_subconjunto( vector< unsigned int >& conjunto, unsigned int mask ){
	unsigned int res = 0;

	for(unsigned int i = 0; i < conjunto.size(); i++){ // && i <= mask
		if ( ( (1<<i) & mask ) > 0 ) // el i-ésimo está contenido en la máscara?
			res += conjunto[i];
	}

	return res;
}

/* Dado un multiconjunto representado como un vector (@Param1) se genera un conjunto de partes,
	luego se completa en otro vector (@param2) el valor resultante de aplicar sumatoria a los elementos en el conjunto de partes 

Complejidad: 2^(|conjunto|) * log( 2^(|conjunto|) ) */
void P1::crear_conjunto_partes_de( vector< unsigned int >& conjunto, vector<unsigned int>& partes_de_conjunto){
	
	partes_de_conjunto.resize( pow( 2, conjunto.size() ) );

	for( unsigned int mask = 0; mask < partes_de_conjunto.size(); mask++ ) 			// se itera 2^(|conjunto|) veces
		partes_de_conjunto[mask] = sumar_elementos_subconjunto( conjunto, mask );		// O(|conjunto|)

	sort( partes_de_conjunto.begin(), partes_de_conjunto.end() ); 					// Ordeno el "conjunto de partes" 
}

/* Dados dos arreglos ordenados ascendentemente. Recorro al primero forma ascendente y al segundo de forma descendente 
buscando la suma de un elemento de cada uno que más se aproxime al presupuesto que homero maneja.

Complejidad: lienal en |mitad_1| */
unsigned int P1::calcular_maxima_compra( vector<unsigned int>& mitad_1, vector<unsigned int>& mitad_2 ){
	unsigned int res = 0;
	int j = mitad_2.size()-1;

	for( unsigned int i = 0; i < mitad_1.size(); i++){
		while( j > 0 && ( mitad_1[i]+mitad_2[j] > this->presupuesto ) )
			j--;

		if( mitad_1[i]+mitad_2[j] <= this->presupuesto && mitad_1[i]+mitad_2[j] > res )
			res = mitad_1[i] + mitad_2[j];
	}

	return res;
}


unsigned int P1::resolver(){
	unsigned int res = 0;
	vector<unsigned int> mitad_1, mitad_2;

	//Genero el conjunto de partes de la primer mitad de packs
	crear_conjunto_partes_de( primer_mitad_packs, mitad_1 );

	//Genero el conjunto de partes de la segunda mitad de packs
	crear_conjunto_partes_de( segunda_mitad_packs, mitad_2 );	

	//Consigo la mayor cantidad de donas que pueda comprar
	res = calcular_maxima_compra( mitad_1, mitad_2 ); 			

	return res;
}