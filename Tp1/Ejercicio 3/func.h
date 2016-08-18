#include <iostream>
#include <vector>

using namespace std;

int debug = 0;

int sumaMax(vector<int> v){
	int max = 0;
	int sumaActual = 0;
	int inicio = 0;
	int actual = 0;

	for (int i = 0; i < v.size(); ++i){

		if(debug){cout << "Iteracion: " << i << endl;}
		int aux = sumaActual;
		if(debug){cout << "Suma Actual: " << sumaActual << endl;}
		sumaActual = sumaActual + v[actual];
		if(debug){cout << "Suma Actual+: " << sumaActual << endl;}		

		if(sumaActual<0){			
			inicio = actual;
			sumaActual = 0;
			actual++;							
		}else{
			if(sumaActual>max){max = sumaActual;}
			if(debug){cout << "Max: " << max << endl;}
			actual++;
		}	
	}

	if(debug){cout << "Inicio: " << inicio << endl;}
	if(debug){cout << "Actual: " << actual << endl;}
	if(debug){cout << "sumaActual: " << sumaActual << endl;}


	return max;
}
