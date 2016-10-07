#include <iostream>
#include <stack>
#include <vector>
#include <queue>

#define NIL -1

using namespace std;

//Una clase o una estructura sería lo mismo
class Calle{
    public:
    int origen;
    int destino;
    Calle(int , int );
    Calle();
    Calle(const Calle&);
    bool operator!=(const Calle& c) const;
};
Calle::Calle(){
    this->origen = -1;
    this->destino = -1;
}
Calle::Calle(int origen, int destino){
    this->origen = origen;
    this->destino = destino;
}
Calle::Calle(const Calle& c){
    this->origen = c.origen;
    this->destino = c.destino;
}
bool Calle::operator!=(const Calle& c) const{
    return (this->origen != c.origen) || (this->destino != c.destino);
}

class Grafo{
    public:
        Grafo(int);
        void    agregarArista(int, int);
        void    BCC();    // prints strongly connected components
        
        /*Queries*/
        int     queryA(int, int);
        bool    queryB(int );
        int     queryC(int );

    private:
        /*Para armar el grafo y aplciar el DFS y BFS casi de pizarra*/
        vector < vector< int > > list_ady;
        vector < vector< int > > list_ady_sin_puentes;
        vector < Calle > calles;
        vector < int > low, depth, parent, numero_componente, componente;
        vector <bool> punto_art;
        
        void    BCCRecursivo(int v, int d, stack<Calle> &calles_visitadas);
        void    rearmarComponenteBiconexaHasta(Calle, stack<Calle>&);
        void    rearmarCompBiconexa(stack<Calle>&);
        
        int     BFS(int, int );
        bool    es_puente(int, int );
        void    BFS_cant_nodos();
        void 	armarGrafoSinPuenteS();
        void	contarNodosPorSubgrafo();
        int  	BFS_contador_nodos( vector<bool> &vis, int v, int num_comp);
};

//El constructor toma la cantidad de nodos del grafo (esquinas del problema)
//Resizeo todas las variables que voy a utilizar en mi clase
Grafo::Grafo(int V){
    list_ady.resize(V);
    list_ady_sin_puentes.resize(V);
    low.resize(V,NIL);
    depth.resize(V,NIL);
    parent.resize(V,NIL);
    numero_componente.resize(V,NIL);
    punto_art.resize(V,false);
}

void Grafo::agregarArista(int v1, int v2){
    calles.push_back(Calle(v1,v2));
    list_ady[v1].push_back(v2);
    list_ady[v2].push_back(v1);
}

//Desapilo hasta cierta arista y las apilo en otra pila para luego llamar a rearmarCompBiconexa.
//La arista hasta tiene que existir en la pila aristas_bcc
void Grafo::rearmarComponenteBiconexaHasta(Calle hasta, stack<Calle> &aristas_bcc){
    stack<Calle> aux;
    
    while( aristas_bcc.top() != hasta ){
        aux.push( aristas_bcc.top() );
        aristas_bcc.pop();
    }
    
    aux.push(aristas_bcc.top());
    aristas_bcc.pop();

    rearmarCompBiconexa(aux);
}

//Desapilo todas las aristas de la pila, cuento la cantidad de elementos, y creo los nodos correspondientes en el black-cut tree
//Cada vez que cierro una componente biconexa, es agregar al menos un nodo al black cut tree
void Grafo::rearmarCompBiconexa(stack<Calle> &aristas_bcc){
    while( aristas_bcc.size() > 0 )
        aristas_bcc.pop();
}

/*Como lo vimos en clase, es recorrer un grafo de la misma manera que DFS lo hace, pero persistiendo más información en arreglos, 
sobre la posición de cada vértice, puntualmente el padre, low, y depth.
Con lo cual después podemos encontrar las diferentes componentes biconexas, los puntos de articulación, y los puentes.*/
//Complejidad: O(N+M) = O(M)
void Grafo::BCCRecursivo(int v, int d, stack<Calle> &calles_visitadas){
    
    //Por defecto mi low y depth es mi profundidad en el arbol DFS
    depth[v] = low[v] = d;
    int c_hijos = 0, h;

    //Recorro todos los vecinos de v
    for (int i = 0; i < list_ady[v].size(); i++){

        h = list_ady[v][i];  // h es vecino de v
   
        if (depth[h] == -1){
            // h no fue visitado hasta ahora
            c_hijos++;
            parent[h] = v;
            
            calles_visitadas.push( Calle(v,h) );

            //Llamado recursivo en mi vecino, siendo h un nivel más profundo que v en el árbol
            BCCRecursivo(h, d+1, calles_visitadas);
   
            low[v]  = min(low[v], low[h]);
  
            if( ( depth[v] == 0 && c_hijos > 1 ) || ( depth[v] > 1 && low[h] >= depth[v] ) ){
                /*v es un punto de articulación.
                Rearmo la componente biconexa con las aristas que sigan en la pila pusheadas desde (v,h).
                A lo sumo todas las aristas del subarbol generado a partir de h entran en esta componente biconexa.*/
                punto_art[v] = true;
                rearmarComponenteBiconexaHasta(Calle(v,h), calles_visitadas);
            }
        
        }else if(h != parent[v] && depth[h] < low[v]){
            low[v]  = min(low[v], depth[h]);
            calles_visitadas.push( Calle(v,h) );
        }
    }
}


void Grafo::BCC(){
    stack<Calle> aristas_visitadas;
   
    //el grafo es conexo, entonces basta lanzar el DFS desde cualquier posición que nos asegura llegará a todos los
    //obs, el nodo 0 no existe, la numeración arranca en 1
    BCCRecursivo( 1, 0, aristas_visitadas);

    //Si la pila no está vacía, popeo todo, es la ultima componente biconexa visitada
    if(aristas_visitadas.size() > 0)
        rearmarCompBiconexa(aristas_visitadas);

    //Genero un grafo sin los puentes
    armarGrafoSinPuenteS();
    //Cuento los nodos de cada subgrafo
    contarNodosPorSubgrafo();
}

//Genero una copia del grafo original pero sin las aristas puentes
//Complejidad: O(N+M) = O(M)
void Grafo::armarGrafoSinPuenteS(){
	for(int i = 0; i < list_ady.size(); i++){
		for(int j= 0; j < list_ady[i].size(); j++){

			if( !es_puente( i, list_ady[i][j]) )
				list_ady_sin_puentes[i].push_back( list_ady[i][j] );
		}
	}
}

//Cuento los nodos de cada subgrafo lanzando BFS desde cada uno y contando la cantidad de elementos
//O(N+M) = O(M)
void Grafo::contarNodosPorSubgrafo(){
	vector < bool > visitados ( list_ady_sin_puentes.size(), false );
	int iteracion = -1;

	for( int i = 1; i< visitados.size(); i++){
		if( !visitados[i] ){
			iteracion++;
			componente.push_back( BFS_contador_nodos( visitados, i, iteracion) );
		}
	}
}

int Grafo::BFS_contador_nodos( vector<bool> &vis, int v, int num_comp){
	
	int contador = 0;
	queue <int> cola;
	cola.push(v);
	vis[v] = 1;

	while(!cola.empty()){
		int w = cola.front();
		contador++;
		numero_componente[w] = num_comp;
		cola.pop();

		for(int i = 0; i < list_ady_sin_puentes[w].size(); i++){
			
			if( !vis[ list_ady_sin_puentes[w][i] ] ){
				cola.push( list_ady_sin_puentes[w][i] );
				vis[ list_ady_sin_puentes[w][i] ] = true;
			}

		}
	}
	return contador;
}

/*  QUERIES */
int Grafo::queryA(int v_inicio, int v_destino){
    return BFS(v_inicio, v_destino);
}
bool Grafo::queryB(int num_calle){
    return es_puente(calles[num_calle].origen, calles[num_calle].destino);
}
int Grafo::queryC(int vertice){
    return componente[ numero_componente[ vertice ] ] - 1; //me resto a mí
}

int main(){
    int V, E, origen, destino, cant_queries, calle, esquina;
    char t_query;

    cin >> V >> E;
    V++;E++;//la numeración arranca en 1 prefiero hacer esto que restar después en cada una

    Grafo g = Grafo(V);

    //Levanto la parte del input del mapa
    for (int i = 1; i < E; ++i){
        cin >> origen >> destino;
        g.agregarArista(origen,destino);
    }

    g.BCC();

    //Leo las querys y voy respondiendo
    cin >> cant_queries;

    for (int i = 0; i < cant_queries; i++){
        // interpretar cada una hacer un llamado a un switch
        cin >> t_query;
        
        switch(t_query){
            case 'A':
                cin >>origen >> destino;
                cout << g.queryA(origen, destino) <<endl;
                break;
            case 'B':
                cin >> calle;
                cout << g.queryB(calle-1) << endl;
                break;
            case 'C':
                cin >> esquina;
                cout << g.queryC(esquina) << endl;
                break;
        }
    }
    return 0;
}

//(v,h) es puente si ( v = parent[h] y depth(h) =< low(h) ) o  ( h = parent[v] y depth(v) =< low(v) ) 
//El parentesco es para asegurarse que efectivamente era un tree edge
bool Grafo::es_puente(int v, int h){
    return ( v == parent[h] && depth[h] <= low[h] ) || ( h == parent[v] && depth[v] <= low[v] );
}

/*
Precondición:
    v_inicio, v_destino son vértices del grafo.

Bfs desde v_inicio hasta v_destino (el grafo es conexo, entonces siempre llego a v_destino)
    Persistiendo un vector de booleanos para no visitar dos veces un mismo vértice.
    Persistiendo un vector de enteros para saber cuantos puentes crucé para llegar hasta ese vértice.
*/
int Grafo::BFS(int v_inicio, int v_destino){
    vector< int > cant_puentes_hasta( list_ady.size(), 0 );
    vector< bool >  visitado ( list_ady.size(), 0 );
    queue < int > vertices;
    int v, vecino;

    /* Inicialización */
    vertices.push(v_inicio);
    visitado[v_inicio] = true;
    cant_puentes_hasta[v_inicio] = 0;
    
    /* BFS de pizarra */
    while( !vertices.empty() ){
                
        v = vertices.front();                           //Veo un vértice de la cola
        vertices.pop();

        for(int i = 0; i < list_ady[v].size(); i++){       //Veo de sus vecinos cuales no visité y los encolo
            vecino = list_ady[v][i];
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