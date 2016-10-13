#include "p2.h"

P2::P2(){
	minT = 0;
	inicializar(&raiz);
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
	palabra es un string a depositar en el Trie
	cant_caracteres es la cantidad de caracteres restantes para marcar al nodo como prefijo de la palabra 

Itero sobre todas las letras de "palabra", las voy colocando en el trie, 
aumentando la cantida de ocurrencias si ya estaba.	

Complejidad:
	O( |palabra| ) * O( inicializar ) = O( |palabra| * 27) = O(|palabra|)
*/ 
void P2::agregarPalabra(string& palabra, int cant_caracteres){
	
	nodo_trie* actual = &raiz;

	for( int i = 0; i < palabra.size(); i++ ){
		if( actual->hijos[ palabra[i]-'A' ] == NULL ){
			actual->hijos[ palabra[i]-'A' ] = new nodo_trie;
			inicializar( actual->hijos[ palabra[i]-'A' ] );
		}
		actual = actual->hijos[ palabra[i]-'A' ];
		actual->cant_ocurrencias++;
		cant_caracteres--;

		//Chequeo si es un prefijo
		if(cant_caracteres == 0)
			actual->esPrefijo = true;
		
		//Si es un prefijo, se aumento la cantidad de ocurrencias, actualizo minT
		if( actual->esPrefijo ){
			max(minT, actual->cant_ocurrencias);
		}
	}
}

/*	Borro el espacio en memoria generado para el Trie	*/
void P2::borrarNodo(nodo_trie *nodo){
	for(int i = 0; i < CANT_LETRAS; i++) 
		if(nodo->hijos[i] != NULL) borrarNodo(nodo->hijos[i]);

	delete nodo;
}

int P2::dameTMin(){
	return minT;
}