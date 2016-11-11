#include <iostream>
#include <vector>

using namespace std;

vector<float> listaEsperanzas;
vector< vector<float> > matrizProbas; 		// Contiene en la posicion i,j la probabilidad de que al hacer un shuffle del subarreglo A[i..n), los primeros j elementos son los menores (y el j+1 no)
vector< vector<int> > comb;

void calcularComb(int n){
	for(int i = 0; i<n+1; i++){
		comb[i][i] = 1;	
		comb[i][0] = 1;	
	}
	for(int i = 1; i<n+1; i++){
		for(int j = 1; j<i; j++){
			comb[i][j] = comb[i-1][j]+comb[i-1][j-1];
		}
	}
}

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
//cout << i << " " << j << " " << matrizProbas[i][j] << endl;
		}
		for(int j = 1; j<n-1-i; j++){
			float probaQueElSiguienteNoSeaMenor;
			probaQueElSiguienteNoSeaMenor = (float )info[i+j]/(n-j-i);
			matrizProbas[i][j] = matrizProbas[i][j]*(1-probaQueElSiguienteNoSeaMenor);
//cout << i << " " << j << " " << matrizProbas[i][j] << endl;
		}
	}
	matrizProbas[n-1][0] = 1;

	
}




float calcularEsperanza(vector<int> arreglo, int desde, int cant){

	if(listaEsperanzas[desde] != -1)
		return listaEsperanzas[desde];
	
	if(desde == cant-1){
		listaEsperanzas[desde] = 0;
		return 0;
	}

	float res = 0;
	for(int i = 1; i<cant-desde; i++){
		//cout << res << endl;
		res += matrizProbas[desde][i] * calcularEsperanza(arreglo, desde+i,cant);
	}

	float esperanza = (res+1)/(1-matrizProbas[desde][0]);
	listaEsperanzas[desde] = esperanza;
	return esperanza;
}

/*
float calcularEsperanza(vector<int> arreglo, vector<int> info, int desde, int cant){

	for(int i = cant-1; i>=0; i--){
		listaEsperanzas[i] = 0;
		for(int j = i; j<cant; j++){
			listaEsperanzas[i] += matrizProbas[i][j-i] * listaEsperanzas[j];
		}		
	}

	return listaEsperanzas[0];
}
*/
int main(){
	
	int n;
	cin >> n;
	vector<int> arreglo;
	for(int i = 0; i<n; i++){
		int val;
		cin >> val;
		arreglo.push_back(val);
	}
	
/*
	int n = 3;
	vector<int> arreglo;
	arreglo.push_back(1);
	arreglo.push_back(2);
	arreglo.push_back(3);
*/
	sort(arreglo.begin(),arreglo.end());
	vector<int> arregloInfoIguales(n,0);


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

	vector<int> vec1(n+1,-1);
	vector< vector<int> > aux1(n+1,vec1);
	comb = aux1;

	calcularComb(n);
	calcularProbas(arreglo, arregloInfoIguales, n);
	float res = calcularEsperanza(arreglo, 0, n);



/*
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cout << matrizProbas[i][j] << "  ";
		}
		cout << endl;
	}
*/
/*
	for(int i = 0; i<n; i++){
		cout << listaEsperanzas[i] << endl;
	}
*/

	cout << res << endl;
	return 0;
}

	// E(todo) = P(A[0] es el menor y A[1] no es el segundo menor) * E(A[1..n)) + ....
	// E([1,2,3]) = P([1,3,2])*E([2,3])+P[1,2,3]*E([])
	//			  = 1/6 * 1/2 + 1/6 = 1/4


