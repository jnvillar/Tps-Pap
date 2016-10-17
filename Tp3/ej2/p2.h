#ifndef __P2_H_INCLUDED__
#define __P2_H_INCLUDED__
#include <iostream>

#define CANT_LETRAS 52
using namespace std;

class P2{

	private:
		typedef struct t_nodo_trie{
			int cant_ocurrencias;
			bool esPrefijo;
			t_nodo_trie* hijos[CANT_LETRAS];

		} nodo_trie;

		int minT;
		nodo_trie raiz;
				
		void inicializar(nodo_trie*);
		void borrarNodo(nodo_trie *nodo);
	public:
		P2();
		~P2();
		void agregarPalabra(string&, int);
		int dameTMin();
};

#endif