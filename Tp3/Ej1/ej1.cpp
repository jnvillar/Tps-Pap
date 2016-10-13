#include <iostream>
#include <string>
#include <vector>

using namespace std;

void completarTablaKMP(string palabra, vector<int> &tablaKMP){
	int pos = 2;				//Posicion a ser computada de la palabra
	int cnd = 0;
	tablaKMP[0] = -1;
	tablaKMP[1] = 0;

	while(pos<palabra.size()){
		if(palabra[pos-1] == palabra[cnd]){
			tablaKMP[pos] = cnd+1;
			cnd++; pos++;
		}
		else if(cnd>0){
			cnd = tablaKMP[cnd];
			tablaKMP[pos] = 0;
		}
		else{
			tablaKMP[pos] = 0;
			pos++;
		}	
	}
}

int main(){
	string a("abcdabd");
	vector<int> tablaKMP(a.size(),-8);

	for (int i = 0; i < tablaKMP.size(); ++i){
		cout << tablaKMP[0] << ",";
	} cout << endl;

	completarTablaKMP(a,tablaKMP);

	for (int i = 0; i < tablaKMP.size(); ++i){
		cout << tablaKMP[0] << ",";
	} cout << endl;

	return 0;
}

