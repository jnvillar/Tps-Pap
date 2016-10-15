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
	
	int pos;
	nodo_trie* actual = &raiz;

	for( int i = 0; i < palabra.size(); i++ ){

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
		actual->cant_ocurrencias++;
		cant_caracteres--;		

		//Chequeo si es un prefijo
		if( cant_caracteres == 0)
			actual->esPrefijo = true;
		
		//Si es un prefijo, se aumento la cantidad de ocurrencias, actualizo minT
		if( actual->esPrefijo )
			minT = max(minT, actual->cant_ocurrencias);
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