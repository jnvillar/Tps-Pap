#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int debug = 0;

int sumaMax(vector<int> v){
	
	int maximo = 0;
	int sumaActual = 0;

	for (int i = 0; i < v.size(); ++i){
		sumaActual = sumaActual + v[i];

		if(sumaActual<0){			
			sumaActual = 0;
		}else{
			maximo = max( sumaActual, maximo);
		}	
	}
	return maximo;
}