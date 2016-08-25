#include "matriz.h"
#include <math.h>
#include <list>
using namespace std;

int main(){
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

	int altura = log2(L)+1;
	vector< vector<Matriz> > listaProductos;
	listaProductos.push_back(listaMtx);
	for(int i = 1; i<altura; i++){
		vector<Matriz> prod;
		for(int j = 0; j<N-1; j++){
			prod.push_back(listaProductos[i-1][j]*listaProductos[i-1][j+i]);
		}
		listaProductos.push_back(prod);
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


	for (int i = 0; i<N-L+1; i++){
		if(posiblesSubmatrices[i] == m){
			cout << "1" << endl;
			return 0;
		}
	}
	cout << "0" << endl;
	return 0;
}

