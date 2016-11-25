#include "p2.h"

P2::P2(){
	minT = 0;
	inicializar(&raiz);
}
P2::~P2(){
	borrarHijos(&raiz);
}

/*
Input:
	n un nodo_trie*

Seteo la cantidad de ocurrecias de ese nodo en 0 y sus hijos en NULL.

Complejidad:
	O(27) = O(1)
*/
void P2::inicializar( nodo_trie* n){
	n->cant_ocurrencias = 0;
	n->esPrefijo = false;
	for(int i = 0; i < CANT_LETRAS; i++)
		n->hijos[i] = NULL;
}

/*	
Input:
	palabra es un string a depositar en el Trie.
	long_prefijo es la cantidad de caracteres restantes para marcar al nodo como prefijo de la palabra.

Complejidad:
	O( |long_prefijo| ) * O( inicializar ) = O( |long_prefijo| * 27) = O(|long_prefijo|) = O(|palabra|)
*/ 
void P2::agregarPalabra(string& palabra, int long_prefijo){
	
	int pos;
	nodo_trie* actual = &raiz;

	for( int i = 0; i < long_prefijo; i++ ){

		//Consigo la posición en el arreglo Hijos
		if( palabra[i] <= 'Z')
			pos = palabra[i] - 'A';
		else
			pos = 26 + palabra[i] - 'a';

		//Si este caracter no estaba en el trie 
		if( actual->hijos[pos] == NULL ){
			actual->hijos[pos] = new nodo_trie;
			inicializar( actual->hijos[pos] );
		}

		actual = actual->hijos[pos];
		
		//Aumento la cantidade veces que paso por este nodo
		actual->cant_ocurrencias++;
		
		//Si es un prefijo, se aumento la cantidad de ocurrencias, actualizo minT
		if( actual->esPrefijo )
			minT = max(minT, actual->cant_ocurrencias);
	}
	//Actual apunta al nodo en el Trie que representa el último caracter del prefijo
	actual->esPrefijo = true;
	minT = max(minT, actual->cant_ocurrencias);
}

/*	Borro el espacio en memoria generado para el Trie	*/
void P2::borrarNodo(nodo_trie *nodo){
	borrarHijos(nodo);
	delete nodo;
}
void P2::borrarHijos(nodo_trie *nodo){
	for(int i = 0; i < CANT_LETRAS; i++){
		if(nodo->hijos[i] != NULL) borrarNodo(nodo->hijos[i]);
	}
}

int P2::dameTMin(){
	return minT;
}