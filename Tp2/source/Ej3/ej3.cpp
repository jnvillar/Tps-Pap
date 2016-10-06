#include "ej3.h"

EJ3::EJ3(){
	int n,m;
	cin >> n >> m;
	n++;m++;
	grafo.resize(n);
	calles.resize(m);

	//Completar el grafo
	for (int i = 0; i < m; ++i){
		cin >> calles[i].desde >> calles[i].hasta;
		grafo[ calles[i].desde ].push_back( calles[i].hasta );
		grafo[ calles[i].hasta ].push_back( calles[i].desde );
	}

	//Inicializo las variables y corro DFS
	init(n);
}

void EJ3::reportarComponenteBiconexa(stack<calle> &pila, calle c){
	//Las calles estan apiladas de la forma (padre,hijo)
	calle c_aux = pila.top();
	c_componentes++;
	int c_nodos = 0;
	while( c_aux.desde != c.desde && c_aux.hasta != c.hasta ){
		if( comp[c_aux.desde] == -1 ){
			comp[c_aux.desde] = c_componentes;
			c_nodos++;
		}
		if( comp[c_aux.hasta] == -1 ){
			comp[c_aux.hasta] = c_componentes; 
			c_nodos++;
		}
		
		pila.pop();
		c_aux = pila.top();
	}
	if( comp[c_aux.desde] == -1 ){
			comp[c_aux.desde] = c_componentes;
			c_nodos++;
	}
	c_nodos_comp.push_back(c_nodos);
	//almacenar c_nodo en un 
	pila.pop();
}


int EJ3::dfs( int v_actual, int actual_depth, int v_padre, stack<calle> &pila){
	depth[v_actual] = low[v_actual] = actual_depth;
	if( v_actual != v_padre )
		pila.push( calle(v_padre, v_actual) );

	for (int i = 0; i < grafo[v_actual].size(); ++i){

		int v_hijo = grafo[v_actual][i];
		
		if ( v_hijo != v_padre ){ 						//el grafo no es dirigido

			if( depth[v_hijo] == -1 ){

				low[v_actual] = min( low[v_actual], dfs(v_hijo, actual_depth+1, v_actual, pila) );

				if( low[v_hijo] >= depth[v_actual] ) 	//el vertice actual es un punto de articulación
					reportarComponenteBiconexa(pila, calle(v_actual,v_hijo));

				//if( low[v_hijo] >= depth[v_hijo] )
					//marcar como puente v_actual v_hijo 

			}else{
				low[v_actual] = min( low[v_actual], depth[v_hijo]);
			}

		}
	}

	return low[v_actual];
}

void EJ3::init(int c_nodos){
	depth.resize(c_nodos);
	low.resize(c_nodos);
	comp.resize(c_nodos);

	for (int i = 0; i < depth.size(); ++i)
		comp[i] = depth[i] = low [i] = -1;

	stack<calle> pila;
	dfs(1,0,1,pila);
}

/* 	QUERIES	*/
int EJ3::queryA(int v_inicio, int v_destino){
	return BFS(v_inicio,v_destino);
}

bool EJ3::queryB(int num_calle){
	return es_puente( calles[num_calle].desde, calles[num_calle].hasta);
}

bool EJ3::queryC(int esquina){
	return cant_en_comp_conexa(esquina) - 1; //me resto yo
}

//es_puente(nodoA,nodoB) == 1 <=> la arista que va de nodoA a nodoB es puente. 0 sino.
bool EJ3::es_puente(int desde, int hasta){ //no estoy muy seguro de que esto sea así no más
	return comp[ desde ] != comp[ hasta ] ; //es puente si los nodos pertenecen a diferentes componentes conexas
}

int EJ3::cant_en_comp_conexa(int esquina){
	return c_nodos_comp[ comp[esquina] ];
}


/*
Precondición:
	v_inicio, v_destino son vértices del grafo.

Bfs desde v_inicio hasta v_destino (el grafo es conexo, entonces siempre llego a v_destino)
	Persistiendo un vector de booleanos para no visitar dos veces un mismo vértice.
	Persistiendo un vector de enteros para saber cuantos puentes crucé para llegar hasta ese vértice.
*/
int EJ3::BFS(int v_inicio, int v_destino){
	vector< int > cant_puentes_hasta( 0, grafo.size() );
	vector< bool >  visitado ( 0, grafo.size() );
	queue < int > vertices;
	int v, vecino;

	/* Inicialización */
	vertices.push(desde);
	visitado[desde] = true;
	cant_puentes_hasta[desde] = 0;
	
	/* BFS de pizarra */
	while( !vertices.empty() ){
				
		v = vertices.front(); 							//Veo un vértice de la cola
		vertices.pop();

		for(int i = 0; i < grafo[v].size(); i++){		//Veo de sus vecinos cuales no visité y los encolo
			vecino = grafo[v][i];
			if( !visitado[vecino] ){
				visitado[vecino] = 1;
				/* 
					Si la arista que tomé para llegar al vecino es puente, la sumo a la cuenta actual.
				
				Obs: Desde v_inicio hasta cualquier vértice, no importa con que camino simple, la cantidad de puentes a cruzar es la misma.
				Si llegase con dos valores distintos al mismo nodo => tome distintos caminos => ese vértice está dentro de un ciclo con v_desde
				=> está en la misma componente biconexa => crucé 0 puentes => Abs!
				*/
				cant_puentes_hasta[vecino] = cant_puentes_hasta[v] + es_puente(v,vecino); 
				vertices.push(vecino);
			}
		}
	}

	return cant_puentes_hasta[v_destino];
}