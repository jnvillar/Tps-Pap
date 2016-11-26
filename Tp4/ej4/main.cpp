#include<iostream>
#include<vector>
using namespace std;


//Escupir comp_conexas
void print_comp_conexas(vector<int>& cc){
	for (int i = 0; i < cc.size(); i++)
		cout << " " << cc[i];
	cout << endl;
}


/*Si hay una Componente conexa con cantidad de vertices par, entonces solución es 0*/
bool hay_ciclo_par(vector<int>& cc){
	bool res = true;
	for (int i = 0; i < cc.size() && res; i++)
		res &= (cc[i]%2 == 0);
	return res;
}

int main(){
	/*El input son cantidad_de_equipos(vértices) y f(1), ..., f(|vértices|-1), con f la función de permutación. */
	int cant_vertices;
	cin >> cant_vertices;
	vector<int> permutacion = vector<int>(cant_vertices);

	for(int i = 0; i < cant_vertices; i++)
		cin >> permutacion[i];

	/*vector de componentes conexas : representada cada una con su cantidad vertices */
	vector<int> comp_conexas; 
	vector<bool> visitado = vector<bool>(cant_vertices,false);

	//El primer vertice lo marco visitado y contado
	int prox, c_cc;
	
	for(int i = 0; i < cant_vertices; i++){
		if( !visitado[i] ){
			/*vertice desde donde formo un ciclo*/
			c_cc = 0;
			prox = i;
			while( !visitado[prox] ){
				visitado[prox] = 1;
				c_cc++;
				cout << "visite "<< prox << " nodos " << c_cc<<endl;
				prox = permutacion[prox]-1;
			}
			comp_conexas.push_back(c_cc);
		}
	}
	
	//print_comp_conexas(comp_conexas);
	int res = 0;
	if( !hay_ciclo_par(comp_conexas) ){
		/*res = 2 ^ ( |V| - 2*#CC + #CC^2 ) */
		int exponente = cant_vertices - 2 * comp_conexas.size() + comp_conexas.size()*comp_conexas.size();
		exponente /=2;
		exponente = exponente%1000000006; //Arbitrariamente piden modulo 1.000.000.007 
		res = (1<<exponente)%1000000007;
		cout << "exponente " << exponente<<endl;
	}
	cout << res << endl;
	return 0;
}