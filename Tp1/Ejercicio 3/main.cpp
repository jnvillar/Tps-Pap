#include "func.h"
using namespace std;

int main(int argc, char *argv[]){

	/*-----------------------------Tests------------------------------	
	testManuales();	
	------------------------------------------------------------------*/

	/*------------------------Entrada por consola---------------	
	vector<int> v;
	int cant;
	cin >> cant;
	for (int i = 0; i<cant; i++){
		int val;
		cin >> val;
		v.push_back(val);
	}
	int res = sumaMax(v);
	------------------------------------------------------------------/*

	

	/*---------------Entrada por archivo de texto-----------*/

	vector<int> a = parser(argv[1]);
	int res = sumaMax(a);	
	cout << res << endl;
	return res;

	/*----------------------------------------------------------------*/
}