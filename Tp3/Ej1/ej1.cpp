#include <iostream>
#include <string>
#include <vector>

using namespace std;

void completarTablaKMP(string palabra, vector<int> &tablaKMP){
	int pos = 2;				
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

int stringMatching(string palabra, string texto){

	vector<int> tablaKMP(palabra.size(),0);
	completarTablaKMP(palabra,tablaKMP);

	int m = 0;
	int i = 0;

	while(m+i< texto.size()){
		if (palabra[i] == texto[m+i]){
			if (i==palabra.size()-1){						
				return m;
			}
			i++;
		}
		else{
			if (tablaKMP[i]>-1){
				m = m+i- tablaKMP[i];
				i = tablaKMP[i];
			}
			else{
				m = m+1;
				i = 0;
			}
		}

	}	
	return texto.size();
}

int main(){
	
	string texto; string palabra;
	cin >> texto; cin >> palabra;		
	int res = stringMatching(palabra,texto);
	
	if (res == texto.size()){
		cout << "N" << endl;
	}
	else{
		cout << "S" << endl;
	}

	return 0;
}
