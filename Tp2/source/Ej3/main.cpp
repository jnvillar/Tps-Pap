#include "ej3.h"
using namespace std;


int main(){
	
	//Inicializo las estructuras
	EJ3 e = EJ3();

	//Leo las querys y voy respondiendo
	int c_queries, desde, hasta, calle, esquina;
	char t_query;
	cin >> c_queries;

	for (int i = 0; i < c_queries; ++i){
		// interpretar cada una hacer un llamado a un switch
		cin >> t_query;
		
		switch(t_query){
			case 'A':
				cin >>desde >> hasta;
				cout << e.queryA(desde, hasta) <<endl;
				break;
			case 'B':
				cin >> calle;
				cout << e.queryB(calle) << endl;
				break;
			case 'C':
				cin >> esquina;
				cout << e.queryC(esquina) << endl;
				break;
			default:
				cout << "Query no válida" << endl;
				break;
		}
	}

	return 0;
}