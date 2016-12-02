#include <iostream>
#include <vector>

using namespace std;

vector<float> listaEsperanzas;
vector< vector<float> > matrizProbas; 		// Contiene en la posicion i,j la probabilidad de que al hacer un shuffle del subarreglo A[i..n), los primeros j elementos son los menores (y el j+1 no)


void calcularProbas(vector<int> arreglo, vector<int> info, int n){
	for(int i = 0; i<n-1; i++){
		float val = 1;
		float probaPrimeroNoEsElMenor = 1 - (float )info[i]/(n-i);		
		matrizProbas[i][0] = probaPrimeroNoEsElMenor;
		for(int j = 1; j<n-i; j++){
			float probaQueSalgaElMenor;
			probaQueSalgaElMenor = (float )info[i+j-1]/(n-j-i+1); 	

			val *= probaQueSalgaElMenor;
			matrizProbas[i][j] = val;
		}
		for(int j = 1; j<n-1-i; j++){
			float probaQueElSiguienteSeaMenor;
			probaQueElSiguienteSeaMenor = (float )info[i+j]/(n-j-i);
			matrizProbas[i][j] = matrizProbas[i][j]*(1-probaQueElSiguienteSeaMenor);
		}
	}
	matrizProbas[n-1][0] = 1;

	
}




float calcularEsperanza(int desde, int n){

	if(listaEsperanzas[desde] != -1)
		return listaEsperanzas[desde];
	
	if(desde == n-1){
		listaEsperanzas[desde] = 0;
		return 0;
	}

	float res = 0;
	for(int i = 1; i<n-desde; i++){
		res += matrizProbas[desde][i] * calcularEsperanza(desde+i,n);
	}

	float esperanza = (res+1)/(1-matrizProbas[desde][0]);
	listaEsperanzas[desde] = esperanza;
	return esperanza;
}

int main(){
	
	int n;
	cin >> n;
	vector<int> arreglo;
	for(int i = 0; i<n; i++){
		int val;
		cin >> val;
		arreglo.push_back(val);
	}
	
	sort(arreglo.begin(),arreglo.end());
	vector<int> arregloInfoIguales(n,0);				// contiene en la posicion i la cantidad de elementos iguales a arreglo[i] en el subarreglo arreglo[i..n)


	arregloInfoIguales[n-1] = 1;
	for(int i = n-2; i>=0; i--){
		if(arreglo[i] == arreglo[i+1])			
			arregloInfoIguales[i] = arregloInfoIguales[i+1]+1;
		else
			arregloInfoIguales[i] = 1;
	}

	vector<float> vec(n,-1);
	vector< vector<float> > aux(n,vec);
	listaEsperanzas = vec;
	matrizProbas = aux;


	if (n ==1){
		cout << 1 << endl;
		return 0;
	}

	calcularProbas(arreglo, arregloInfoIguales, n);
	float res = calcularEsperanza(0, n);

	cout << res << endl;
	return 0;
}


