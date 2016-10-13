#include "p2.h"
using namespace std;

int main(){
	int cant_palabras,cant_caracteres;
	string palabra;
	P2 p = P2();

	cin >> cant_palabras;
	for(int i = 0; i < cant_palabras; i++){
		cin >> palabra >> cant_caracteres;
		p.agregarPalabra(palabra, cant_caracteres);
	}

	cout << p.dameTMin();

	return 0;
}