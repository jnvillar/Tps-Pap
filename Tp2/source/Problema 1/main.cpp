#include <iostream>
#include <vector>

using namespace std;

class nodo{
	public:
		nodo(char tipo);
		char tipo();
		void agregarVecino(int vecino);
		
	private:
		char queRepresento;
		vector<int> adyacencias;
};

nodo::nodo(char tipo){
	queRepresento = tipo;
	vector<int> v;
	adyacencias = v;
}

char nodo::tipo(){
	return queRepresento;
}

void nodo::agregarVecino(int vecino){
	adyacencias.push_back(vecino);
}

class problemaUno{
	public:
		problemaUno();
		int resolver();
		void parser();
	private:
		vector<nodo> nodos;
		vector<int> posEscuelas;
		vector<int> porAlumnos;

		int cantNodos;
		int cantAristas;
};

problemaUno::problemaUno(){
	parser();
}



void problemaUno::parser(){
	cin >> cantNodos;
	cin >> cantAristas;

	cout << "Nodos" << endl;

	for (int i = 0; i < cantNodos; i++){
		char caracter;
		cin >> caracter;
		
		if (caracter == 'E'){
			nodo nodoEscuela('E');
			nodo nodoEscuela()
			nodos.push_back(nodoEscuela);
			posEscuelas.push_back(i);
		}
		if (caracter == 'A'){
			nodo nodoAlumno('A');
			nodos.push_back(nodoAlumno);
			porAlumnos.push_back(i);
		}
		if (caracter == 'X'){
			nodo nodoEsquina('X');
			nodos.push_back(nodoEsquina);
		}
	}

	cout << "Aristas" << endl;

	for (int i = 0 ; i < cantAristas; i++){
		int nod1,nod2;
		cin >> nod1;
		cin >> nod2;

		nod1--;
		nod2--;

		nodos[nod1].agregarVecino(nod2);
		nodos[nod2].agregarVecino(nod1);
	}
} 

int main(int argc, char const *argv[])
{
	problemaUno a;
	return 0;
}