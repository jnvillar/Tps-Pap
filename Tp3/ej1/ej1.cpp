#include <iostream>
#include <string>
#include <vector>

using namespace std;

void completarTablaKMP(string palabra, vector<int> &tablaKMP){
	int pos = 1;				
	int cnd = 0;
	tablaKMP[0] = 0;


	while(pos<palabra.size()){
		if(palabra[pos] == palabra[cnd]){
			tablaKMP[pos] = cnd+1;
			cnd++; pos++;
		}
		else if(cnd>0){
			cnd = tablaKMP[cnd-1];
		}
		else{
			tablaKMP[pos] = 0;
			pos++;
		}	
	}

for (int i = 0; i < tablaKMP.size(); ++i)
{
	cout << tablaKMP[i] << " ";
}
cout << endl;

}

int stringMatching(string palabra, string texto){

	vector<int> tablaKMP(palabra.size(),0);
	completarTablaKMP(palabra,tablaKMP);

	int m = 0;
	int i = 0;

	while(m<texto.size()){
		if (palabra[i] == texto[m]){
			if (i==palabra.size()-1){						
				return m;
			}
			i++;
			m++;
		}
		else{
			if (i != 0){
				i = tablaKMP[i-1];
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
