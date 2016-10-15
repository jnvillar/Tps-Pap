#include "func.h"
using namespace std;

int main(int argc, char *argv[]){

	/*-----------------------------Tests------------------------------	
	testManuales();	
	------------------------------------------------------------------*/

	/*------------------------Entrada por consola---------------*/	
	vector<int> v;
	int cant;
	cin >> cant;
	v.resize(cant);
	for (int i = 0; i<cant; i++)
		cin >> v[i];
	cout << sumaMax(v) << endl;
	/*------------------------------------------------------------------/*

	

	/*---------------Entrada por archivo de texto-----------*/
	/*
	vector<int> a = parser(argv[1]);
	int res = sumaMax(a);	
	cout << res << endl;
	return res;
	*/
	/*----------------------------------------------------------------*/
}