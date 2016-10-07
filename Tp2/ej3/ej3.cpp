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

class GrafoCondenso{
    public:
        vector< vector< int > > list_ady; //lista de adyacencias
        vector< int > cant_nodos;
        GrafoCondenso();
        void agregarVertice(int );
        void agregarArista(int, int);
};

GrafoCondenso::GrafoCondenso(){}
void GrafoCondenso::agregarArista(int v1, int v2){
    list_ady[v1].push_back(v2);
    list_ady[v2].push_back(v1);
}
void GrafoCondenso::agregarVertice(int c_nodos){
    vector<int> vacio;
    list_ady.push_back(vacio);          //lista de vecinos vacía nueva
    cant_nodos.push_back(c_nodos);   //nueva cant_vecinos
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
        
        /*TESTING*/
        void    info();
        void    puentes();
        void    todasLasC();

    private:
        /*Para armar el grafo y aplciar el DFS y BFS casi de pizarra*/
        vector < vector< int > > list_ady;
        vector < Calle > calles;
        vector < int > low, depth, parent, numero_componente;
        vector <bool> punto_art;
        
        /* Para condensar el grafo */
        int     contador_componentes;
        GrafoCondenso g_condenso;

        void    BCCRecursivo(int v, int d, stack<Calle> &calles_visitadas);
        void    rearmarComponenteBiconexaHasta(Calle, stack<Calle>&);
        void    rearmarCompBiconexa(stack<Calle>&);
        
        int     BFS(int, int );
        bool    es_puente(int, int );
        void    BFS_cant_nodos();
};

//El constructor toma la cantidad de nodos del grafo (esquinas del problema)
//Resizeo todas las variables que voy a utilizar en mi clase
Grafo::Grafo(int V){
    list_ady.resize(V);
    low.resize(V,NIL);
    depth.resize(V,NIL);
    parent.resize(V,NIL);
    numero_componente.resize(V,NIL);
    punto_art.resize(V,false);
    contador_componentes=0;
}

void Grafo::agregarArista(int v1, int v2){
    calles.push_back(Calle(v1,v2));
    list_ady[v1].push_back(v2);
    list_ady[v2].push_back(v1);
}

//Desapilo hasta cierta arista y las apilo en otra pila para luego llamar a rearmarCompBiconexa.
//La arista hasta tiene que existir en la pila aristas_bcc
void Grafo::rearmarComponenteBiconexaHasta(Calle hasta, stack<Calle> &aristas_bcc){
    //cout << "rearmarComponenteBiconexaHasta::Size " << aristas_bcc.size() << endl;
    //cout << "From " << aristas_bcc.top().origen << "--" << aristas_bcc.top().destino << " " << "to" << hasta.origen << "--" << hasta.destino <<endl;
    stack<Calle> aux;
    while( aristas_bcc.top() != hasta ){
        aux.push(aristas_bcc.top());
        //cout << aristas_bcc.top().origen << "--" << aristas_bcc.top().destino << " ";
        aristas_bcc.pop();
    }
    //cout << aristas_bcc.top().origen << "--" << aristas_bcc.top().destino;
    aux.push(aristas_bcc.top());
    aristas_bcc.pop();
    rearmarCompBiconexa(aux);
    cout << endl;
}

//Desapilo todas las aristas de la pila, cuento la cantidad de elementos, y creo los nodos correspondientes en el black-cut tree
//Cada vez que cierro una componente biconexa, es agregar al menos un nodo al black cut tree
void Grafo::rearmarCompBiconexa(stack<Calle> &aristas_bcc){
    //cout << "rearmarCompBiconexa::Size " << aristas_bcc.size() << endl; 
    
    //aristas_bcc.size() == 1 <=> aristas_bcc.top() es puente
    int aux, cant_nodos = 0; 
    vector<int> vertices;
    vector<bool> recorridos;

    int nro_componente_actual = contador_componentes;
    contador_componentes++;
    
    //Creo mi nodo en el grafo condensado
    g_condenso.agregarVertice(0);

    //Me armo un arreglo con las aristas por facilidad
    while( aristas_bcc.size() > 0 ){
        //cout << aristas_bcc.top().origen << "--" << aristas_bcc.top().destino << " ";
        vertices.push_back(aristas_bcc.top().destino);
        vertices.push_back(aristas_bcc.top().origen);
        cout << aristas_bcc.top().origen << "--" << aristas_bcc.top().destino << " " << endl;
        aristas_bcc.pop();
    }

    for(int i = 0; i < vertices.size(); i++){
        cout << "Vertice " << vertices[i]<< endl;
        if( numero_componente[ vertices[i] ] < nro_componente_actual ){
            if( numero_componente[ vertices[i] ] == NIL){
                //Este vértice no estaba en ninguna otra componente
                cant_nodos++;
                
                if( punto_art[vertices[i]]){    //puede ser pto de art

                    //lo agrego al grafo, y agrego una arista con esta componente
                    g_condenso.agregarVertice(cant_nodos);
                    g_condenso.agregarArista(nro_componente_actual, contador_componentes);
                    numero_componente[ vertices[i] ] = contador_componentes;
                    cout << "punto de art "<< vertices[i] << "como comp " << contador_componentes << endl;
                    cout << "Arista 2 nueva de " << nro_componente_actual << " a " << contador_componentes<<endl;
                    contador_componentes++;
                }else{
                    //Figurará como parte de esta componente, para las futuras componentes biconexas.
                    numero_componente[ vertices[i] ] = nro_componente_actual; 
                }
            }
            else {
                //En este punto, el vértice en cuestión no pertence a esta componente pero ya está agregado en otra. 
                //Entonces la componente biconexa donde pertenece está en g_condenso.
                
                /* vertices.size() >= 2 porque no hay nodos aislados (G conexo). 
                    Este nodo es un punto de articulación que cerro un ciclo con depth mayor.
                    Si es 2, entonces este vértice es pto de art con una componente que tiene un puente. No suma en nuestro caso más que si mismo.
                    Si es > 2, entonces este punto de art permite llegar a vértices de otra componente biconexa, y suma la cantidad de su componente.*/
                    
                if( vertices.size() > 2 ){
                    aux = g_condenso.cant_nodos[ numero_componente[ vertices[i] ] ];
                    aux = aux * (aux > 2) + 1 * (aux <= 2);
                }
                else{
                    aux = 1;
                }

                cant_nodos += aux;
                
                //(Desde_actual_componente , Hasta_pto_de_art)
                cout << "Arista 1 nueva de " << nro_componente_actual << " a " << numero_componente[ vertices[i] ]<<endl;
                cout << "Agrego " << aux << " nodos " << endl;
                g_condenso.agregarArista( nro_componente_actual, numero_componente[ vertices[i] ]);

                if( vertices.size() > 2){
                    //Notar que si ya estaba en otra componente, ponerlo en esta es hacer que esté en una comp con el min de cant_nodos
                    //Entonces no sirve.
                    numero_componente[ vertices[i] ] = nro_componente_actual;
                }
            }
        }
    }

    //Agrego al vértice en el grafo condensado que representa esta componente, 
    //la cantidad de vértices a los que puede llegar con las reglas de la QueryC
    g_condenso.cant_nodos[nro_componente_actual] = cant_nodos;

    cout << "La componente conexa nro " << nro_componente_actual << " termino con " << cant_nodos << endl;
}

// A recursive function that finds and prints strongly connected
// components using DFS traversal
// v --> The vertex to be visited next
// aristas_visitadas -- >> To store visited edges
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
            
            //Apilo la calle hasta mi vecino
            //cout << "Apilo " << v << " " << h <<endl;
            calles_visitadas.push( Calle(v,h) );
            //cout << "TOP " << calles_visitadas.top().origen << " " << calles_visitadas.top().destino <<endl;
            //info();

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
            //cout << "Apilo " << v << " " << h <<endl;
            calles_visitadas.push( Calle(v,h) );
            //cout << "TOP " << calles_visitadas.top().origen << " " << calles_visitadas.top().destino <<endl;
            //info();
        }
    }
}

/*
Se recorren las componentes biconexas en el grafo condensado, en orden de decreciente de finalización ( Ultima en finalizar -> primera en finalizar )
En el DFS anterior, cuando una componente biconexa se formaba, si contenía puntos de articulación que pertenecían a otras componenentes
y estas no fueran puentes, se incluían la cantidad de vértices de esa componente para la queryC.

Pero para cumplir con las complejidades, en vez de actualizar cada rama, cada vez que se incrementara la máxima cantidad de "vértices compartidos",
Se dejó el resultado en las componentes biconexas con mayor tiempo de finalización, y desde ahí se actualiza ahora con BFS. 
*/
void Grafo::BFS_cant_nodos(){
    /*cout << "lista de ady" <<endl;
    for (int i = 0; i < g_condenso.list_ady.size();i++){
        cout << "comp " << i << endl;
        for(int j=0; j < g_condenso.list_ady[i].size(); j++){
            cout << " " <<  g_condenso.list_ady[i][j];
        }
        cout <<endl;
    }*/
    queue <int> cola;
    vector <bool> recorridos (g_condenso.cant_nodos.size(),false);
    int v,w;
    //Encolo la última componente que finalizó

    recorridos[g_condenso.cant_nodos.size()-1] = true;
    cola.push(g_condenso.cant_nodos.size()-1);

    while(!cola.empty()){
        v = cola.front();
        cola.pop();

        for(int i = 0; i < g_condenso.list_ady[v].size(); i++){
            w = g_condenso.list_ady[v][i];
            //cout << "w " << w<<endl;
            if(!recorridos[w]){
                recorridos[w] = true;
                cola.push(w);

                //si w no es un puente ( != 2), entonces v lo contó para calcular su cantidad de nodos
                if( g_condenso.cant_nodos[w] > 2 || g_condenso.cant_nodos[w] == 1 ) 
                    g_condenso.cant_nodos[w] = max(g_condenso.cant_nodos[v], g_condenso.cant_nodos[w]);
            }
        }
    }

}

// The function to do DFS traversal. It uses BCCRecursivo()
void Grafo::BCC(){
    stack<Calle> aristas_visitadas;
   
    //el grafo es conexo, entonces basta lanzar el DFS desde cualquier posición que nos asegura llegará a todos los
    //obs, el nodo 0 no existe, la numeración arranca en 1
    BCCRecursivo( 1, 0, aristas_visitadas);

    //Si la pila no está vacía, popeo todo, es la ultima componente biconexa visitada
    if(aristas_visitadas.size() > 0)
        rearmarCompBiconexa(aristas_visitadas);

    BFS_cant_nodos();
}

/*  QUERIES */
int Grafo::queryA(int v_inicio, int v_destino){
    return BFS(v_inicio, v_destino);
}
bool Grafo::queryB(int num_calle){
    return es_puente(calles[num_calle].origen, calles[num_calle].destino);
}
int Grafo::queryC(int vertice){
    return g_condenso.cant_nodos[ numero_componente[ vertice ] ] * (g_condenso.cant_nodos[ numero_componente[ vertice ] ] != 2) ; //no me resto porque no me cuento
}

int main(){
/*
    Grafo g(10);
    g.agregarArista(9,1);
    g.agregarArista(1,2);
    g.agregarArista(2,3);
    g.agregarArista(3,4);
    g.agregarArista(1,4);
    g.agregarArista(1,5);
    g.agregarArista(6,5);
    g.agregarArista(6,7);
    g.agregarArista(1,7);
    g.agregarArista(6,8);
    g.BCC();*/

/*
//TESTING queryA
    cout << "desde 1 a 8 " << g.queryA(1,8)<<endl;
    cout << "desde 8 a 1 " << g.queryA(8,1)<<endl;
    cout << "desde 8 a 9 " << g.queryA(8,9)<<endl;
    cout << "desde 9 a 8 " << g.queryA(9,8)<<endl;
    cout << "desde 1 a 6 " << g.queryA(1,6)<<endl;
    cout << "desde 2 a 6 " << g.queryA(2,6)<<endl;
    cout << "desde 3 a 9 " << g.queryA(3,9)<<endl;
    cout << "desde 3 a 8 " << g.queryA(3,8)<<endl;
*/


//TESTING queryB
    //g.puentes();

//TESTING queryC
    //g.todasLasC();

    //cout << "Above are " << count << " biconnected components in graph";
//

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
    cout <<endl;    
    cin >> cant_queries;

    for (int i = 0; i < cant_queries; i++){
        // interpretar cada una hacer un llamado a un switch
        cin >> t_query;
        
        switch(t_query){
            case 'A':
                cin >>origen >> destino;
                cout << "query A" << origen << " " <<destino<<endl;
                cout << g.queryA(origen, destino) <<endl;
                break;
            case 'B':
                cin >> calle;
                cout << "query B " <<calle<<endl;
                cout << g.queryB(calle-1) << endl;
                break;
            case 'C':
                cin >> esquina;
                cout << "query C " <<esquina<<endl;
                cout << g.queryC(esquina) << endl;
                break;
        }
    }

    //g.puentes();
    g.todasLasC();
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




/*TESTING*/

void Grafo::info(){
    cout << "parent: ";
    for(int i = 0; i< parent.size();i++){
        cout << parent[i] << " ";
    }
    cout << endl;
    cout << "low:    ";
    for(int i = 0; i< low.size();i++){
        cout << low[i] << " ";
    }
    cout << endl;
    cout << "depth:  ";
    for(int i = 0; i< depth.size();i++){
        cout << depth[i] << " ";
    }
    cout << endl;
}
void Grafo::puentes(){
    cout << "testeando puentes" <<endl;
    for(int i = 0; i< calles.size(); i++){
        cout << calles[i].origen <<"--" << calles[i].destino << " "<< queryB(i)<<endl;
    }
}
void Grafo::todasLasC(){
        for(int i =1; i < list_ady.size(); i++)
            cout << i << " tiene "<< queryC(i) << " cant bcc con el " << endl;
}