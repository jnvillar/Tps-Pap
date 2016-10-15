#include "matriz.h"
#include <math.h>
#include <stdlib.h>   
#include <time.h>   
using namespace std;


bool prodMtx(vector<Matriz> listaMtx, Matriz m, int L, int N){
	int altura = log2(L)+1;
	vector<Matriz> vacio;
	vector< vector<Matriz> > listaProductos(altura,vacio);			// CADA POSICION (i=0..altura-1) DEL VECTOR listaProductos CONTIENE TODAS LAS SUBMATRICES QUE RESULTAN DE MULTIPLICAR 2^i MATRICES
	listaProductos[0] = listaMtx;
	for(int i = 1; i<altura; i++){
		int tamanio = listaProductos[i-1].size()-pow(2,i-1);
		Matriz vacia;
		vector<Matriz> prod(tamanio,vacia);
		for(int j = 0; j<tamanio; j++){
			prod[j] = listaProductos[i-1][j]*listaProductos[i-1][j+pow(2,i-1)];
		}
		listaProductos[i] = prod;
	}
	vector<Matriz> posiblesSubmatrices = listaProductos[listaProductos.size()-1];
	int cantMatricesUtilizadas = pow(2,altura-1);
	while (cantMatricesUtilizadas<L){

		altura--;
		if (cantMatricesUtilizadas+pow(2,altura-1)<=L){
			for(int i = 0; i<N-L+1; i++){
				posiblesSubmatrices[i] = posiblesSubmatrices[i]*listaProductos[altura-1][i+cantMatricesUtilizadas];
			}
			cantMatricesUtilizadas += pow(2,altura-1);
		}
	}

	bool res = false;;
	for (int i = 0; i<N-L+1; i++){
		if(posiblesSubmatrices[i] == m){
			res = true;
		}
	}

	return res;
}


bool prodMtxCuad(vector<Matriz> listaMtx, Matriz m, int L, int N){
	for (int i = 0; i < N-L+1; i++){
		Matriz prod = id();
		for(int j = 0; j<L; j++){
			prod = prod*listaMtx[i+j];
		}
		if (prod == m){
			return true;
		}
	}
	return false;
}


void testRandom(int cantTest){
	for (int i = 0; i < cantTest; ++i){
		srand(time(NULL));
		int N,L;
		N = (rand()%100)+1;				// CANTIDAD DE MATRICES
		L = (rand()%(N-1))+1;				// LONGITUD DEL SUBARREGLO BUSCADO
		vector<int> vec;
		for (int i = 0; i<9; i++){			// OBTENGO M
			int val;
			val = rand()%10007;
			vec.push_back(val);
		}
		Matriz m(vec);
		vector<Matriz> listaMtx;
		for (int i = 0; i<N; i++){			// OBTENGO LA LISTA DE MATRICES
			vec.clear();
			for (int i = 0; i<9; i++){
				int val;
				val = rand()%10007;
				vec.push_back(val);
			}
			Matriz mtx(vec);
			listaMtx.push_back(mtx);
		}


		bool res = prodMtx(listaMtx,m,L,N);
		bool resCuad = prodMtxCuad(listaMtx,m,L,N);
		if (res != resCuad){
			cout << "Algo esta mal" << endl;
		} else {
			//cout << "Todo bien" << endl;
		}
	}
}

void testTrue(int cantTest){
	srand(time(NULL));

	for (int i = 0; i < cantTest; ++i){
		int N,L;
		N = (rand()%100)+1;				// CANTIDAD DE MATRICES
		L = (rand()%N)+1;				// LONGITUD DEL SUBARREGLO BUSCADO
		vector<int> vec;
		vector<Matriz> listaMtx;
		for (int i = 0; i<N; i++){			// OBTENGO LA LISTA DE MATRICES
			vec.clear();
			for (int i = 0; i<9; i++){
				int val;
				val = rand()%10007;
				vec.push_back(val);
			}
			Matriz mtx(vec);
			listaMtx.push_back(mtx);
		}
		Matriz m = id();
		int desde = rand()%(N-L+1);
		for(int i = 0; i<L; i++){
			m = m*listaMtx[desde+i];
		}
		bool res = prodMtx(listaMtx,m,L,N);
		bool resCuad = prodMtxCuad(listaMtx,m,L,N);

		if (!res){
			cout << "Algo esta mal" << endl;
			cout << N << " " << L << endl;
			cout << m << endl;

			for(int i = 0; i<listaMtx.size(); i++){
				cout << listaMtx[i] << endl;
			}
			cout << "Desde: " << desde << endl;
		}
		if(!resCuad){
			cout << "resCuad esta mal o el test esta mal" << endl;
		}
	}
}

int main(){
	/*
	int N,L;
	cin >> N;				// CANTIDAD DE MATRICES
	cin >> L;				// LONGITUD DEL SUBARREGLO BUSCADO
	vector<int> vec;
	for (int i = 0; i<9; i++){			// OBTENGO M
		int val;
		cin >> val;
		vec.push_back(val);
	}
	Matriz m(vec);
	vector<Matriz> listaMtx;
	for (int i = 0; i<N; i++){			// OBTENGO LA LISTA DE MATRICES
		vec.clear();
		for (int i = 0; i<9; i++){
			int val;
			cin >> val;
			vec.push_back(val);
		}
		Matriz mtx(vec);
		listaMtx.push_back(mtx);
	}

	if (prodMtx(listaMtx,m,L,N)){
		cout << "TRUE" << endl;
	} else {
		cout << "FALSE" << endl;
	}*/
	testTrue(10000);
	

	return 0;
}

