#include <iostream>
#include <queue>

using namespace std;



bool todosVisitados(vector<bool> vec){
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == false){
			return false;
		}
	}
	return true;
}

int algunoNoVisitado(vector<bool> vec){
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == false){
			return i;
		}
	}
}

int main(){
	//int n,m,r,e;

/*
	cin >> n;
	cin >> m;
	cin >> r;
	cin >> e;
	vector<int> vacio;
	vector< vector<int> > listaAdy(n,vacio);
	int desde,hasta;


	for(int i = 0; i<m; i++){
		cin >> desde;
		cin >> hasta;
		desde--;
		hasta--;
		listaAdy[desde].push_back(hasta);
		listaAdy[hasta].push_back(desde);
	}*/

	int n= 9,m=6,r=11,e=12;
	vector< vector<int> > listaAdy;
	int desde,hasta;

	vector<int> lista1;
	lista1.push_back(1);
	vector<int> lista2;
	lista2.push_back(2);
	lista2.push_back(0);
	vector<int> lista3;
	lista3.push_back(1);
	vector<int> lista4;
	lista4.push_back(4);
	vector<int> lista5;
	lista5.push_back(3);
	lista5.push_back(5);
	vector<int> lista6;
	lista6.push_back(4);
	lista6.push_back(6);
	vector<int> lista7;
	lista7.push_back(5);
	lista7.push_back(8);
	vector<int> lista8;
	vector<int> lista9;
	lista9.push_back(6);

	listaAdy.push_back(lista1);
	listaAdy.push_back(lista2);
	listaAdy.push_back(lista3);
	listaAdy.push_back(lista4);
	listaAdy.push_back(lista5);
	listaAdy.push_back(lista6);
	listaAdy.push_back(lista7);
	listaAdy.push_back(lista8);
	listaAdy.push_back(lista9);

	vector<int> cantNodos;
	vector<int> cantAristas;

	vector<bool> visitado(n,false);
	queue<int> aVisitar;
	int indice = 0;
	
	while(!todosVisitados(visitado)){
		int prox = algunoNoVisitado(visitado);	
		aVisitar.push(prox);
		visitado[prox] = true;
		cantNodos.push_back(0);
		cantAristas.push_back(0);
		cantNodos[indice] = 1;
		cantAristas[indice] =  listaAdy[prox].size();
		while(!aVisitar.empty()){
			int nodo = aVisitar.front();
			aVisitar.pop();
			for(int i = 0; i<listaAdy[nodo].size();i++){
				if (!visitado[listaAdy[nodo][i]]){
					aVisitar.push(listaAdy[nodo][i]);
					visitado[listaAdy[nodo][i]] = true;
					cantNodos[indice]++;
					cantAristas[indice] +=  listaAdy[listaAdy[nodo][i]].size();
				}
			}
		}
		
		indice++;
	}
	/*
	int cnodos, caristas;
	for(int i =0; i< visitado.size(); i++ ){

		aVisitar.push(algunoNoVisitado(visitado));
		visitado[algunoNoVisitado(visitado)] = true;

		cnodos = 1;
		caristas = listaAdy[algunoNoVisitado(visitado)].size();
		
		while(!aVisitar.empty()){
			int nodo = aVisitar.front();
			aVisitar.pop();
			for(int i = 0; i<listaAdy[nodo].size();i++){
				if (!visitado[listaAdy[nodo][i]]){
					aVisitar.push(listaAdy[nodo][i]);
					visitado[listaAdy[nodo][i]] = true;
					cantNodos[indice]++;
					cantAristas[indice] +=  listaAdy[listaAdy[nodo][i]].size();
				}
			}
		}

		cantNodos.push_back(cnodos);
		cantAristas.push_back(caristas);
	}
	*/


	for(int i = 0; i< cantAristas.size();i++){
		cout << "CantAristas: " << cantAristas[i] << endl;
		cout << "CantNodos: " << cantNodos[i] << endl;
	}

	int res = 0;
	for(int i = 0; i< cantAristas.size();i++){
		if (cantNodos[i]*e > r*(cantNodos[i]*(cantNodos[i]-1)/2 - cantAristas[i]/2)){
			res += r*(cantNodos[i]*(cantNodos[i]-1)/2 - cantAristas[i]/2);
		} else {
			res += cantNodos[i]*e;
		}
	}
	cout << res << endl;
	return 0;
}