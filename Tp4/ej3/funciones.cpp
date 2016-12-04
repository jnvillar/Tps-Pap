#include "clases.cpp"
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <utility>      // std::pair

// Para activar modo debug setear DEBUG_STATUS true
#define DEBUG_STATUS false  

bool menorAngulo(Punto p1, Punto p2) {
    // p1 < p2 ?
    if (p1.getY() >= 0 && p2.getY() < 0)
        return true;

    if (p1.getY() < 0 && p2.getY() >= 0)
        return false;

    double pc = p1.prodCruz(p2);
    return (pc > 0); 
}

void imprimirPuntos(vector<Punto> puntos) {
    cout << "[";
    int size = puntos.size();
    for (int i = 0; i < size; i++) {
        puntos[i].imprimir();
        if (i != size - 1)
            cout << ",";    
    }
    cout << "]\n";
}

vector<Punto> ordenarPuntosSentidoAntihorario(Punto centro, vector<Punto> puntos) {
    vector<Punto> puntosOrdenados;
    for (int i = 0; i < puntos.size(); i++) {
        if (!(centro == puntos[i] || puntos[i].getY() < centro.getY())) {
            puntos[i].restar(centro);
            puntosOrdenados.push_back(puntos[i]);
        }
    }
    sort(puntosOrdenados.begin(), puntosOrdenados.end(), menorAngulo);
    return puntosOrdenados;
}

vector<Punto> centrar(Punto centro, vector<Punto> puntos) {
    for (int i = 0; i < puntos.size(); i++) {
        puntos[i].restar(centro);
    }
    return puntos;
}

pair < vector<Punto>, vector<Punto> > parsear() {
    bool debug = DEBUG_STATUS;

    // parseo h  
    int h;
    cin >> h;
    if (debug) cout << "H: " << h << " \n"; 

    // parseo e
    int e;
    cin >> e;
    if (debug) cout << "E: " << e << " \n"; 

    // parseo puntos historicos
    vector<Punto> puntosHist;
    for (int i = 0; i < h; i++) {
        int x;
        cin >> x;
        int y;
        cin >> y; 
        Punto p(x, y);
        puntosHist.push_back(p);
    }

    if (debug) {
        cout << "Puntos historicos: \n";
        imprimirPuntos(puntosHist);
    }

    // parseo puntos enemigos
    vector<Punto> puntosEnem;
    for (int i = 0; i < e; i++) {
        int x;
        cin >> x;
        int y;
        cin >> y; 
        Punto p(x, y);
        puntosEnem.push_back(p);
    }

    if (debug) {
        cout << "Puntos enemigos: \n";
        imprimirPuntos(puntosEnem);
    }

    pair < vector<Punto>, vector<Punto> > res(puntosHist, puntosEnem);
    return res;
}

int murallaMaxima(vector<Punto> historicos, vector<Punto> enemigos) {
    int h = historicos.size();
    int e = enemigos.size();
    // en maximo lo guardo el maximo parcial, que al finalizar las iteraciones de los ciclos sera el resultado final
    int maximo = 1;
    // itero sobre los puntos historicos tomando en cada iteracion al punto historicos[i] como punto central a partir del cual construyo el poligono
    for (int i = 0; i < h; i++) {
        Punto centro = historicos[i];
        if (DEBUG_STATUS){
            cout << "Punto central = ";
            centro.imprimir();
            cout << endl;
        }
        vector<Punto> puntosOrdenados = ordenarPuntosSentidoAntihorario(centro, historicos);
        vector<Punto> enemigosCentrados = centrar(centro, enemigos);
        // como ya centramos al resto de los puntos con respecto a centro, ahora el centro es (0,0)
        centro.setX(0);
        centro.setY(0);

        if (DEBUG_STATUS){
            cout << "Puntos ordenados y centrados: ";
            imprimirPuntos(puntosOrdenados);
            cout << "Puntos enemigos centrados: \n";
            imprimirPuntos(enemigosCentrados);
        }

        // itero sobre puntosOrdenados tomando en cada iteración a la recta (puntosOrdenados[i],puntosOrdenados[j]) como punto inicial 
        int size = puntosOrdenados.size();
        for (int j = 0; j < size; j++) {
            // construyo un vector para guardar soluciones parciales. Utilizo los ultimos h-1-j elementos del mismo. No utilizo directamente un
            // vector de tamaño h-1-j para no tener que hacer tantas cuentas con los indices a la hora de acceder
            pair<int, Punto> init(2, centro);
            vector< pair<int, Punto> > subsoluciones(h-1, init);

            // itero sobre puntosOrdenados a partir de la posición j+1 y en cada iteracion busco la mejor solución para el subconjunto de puntos incluido en
            // [puntosOrdenados[j+1] ; puntosOrdenados[k]], con la condicion de que dicha solucion incluya al punto puntosOrdenados[k]
            for (int k = j+1; k < size; k++) {
                // itero sobre las subsoluciones previemente calculadas, para poder calcular la que estoy buscando
                for (int z = j; z < k; z++) {
                    // verifico que el poligono sea convexo
                    Punto p1 = puntosOrdenados[k];
                    Punto p2 = subsoluciones[z].second;
                    p1.restar(puntosOrdenados[z]);
                    p2.restar(puntosOrdenados[z]);
                    double pc = p1.prodCruz(p2);
                    // si el resultado es menor que 0 entonces es concavo y no es solución. Entonces, salto a la siguiente iteración.
                    if (pc < 0) continue;
                    // verifico que dentro del triangulo que estoy agregando no hayan enemigos
                    Triangulo t(centro, puntosOrdenados[k], puntosOrdenados[z]);
                    
                    if (DEBUG_STATUS){
                        cout << "Triangulo = ";
                        centro.imprimir();
                        puntosOrdenados[k].imprimir();
                        puntosOrdenados[z].imprimir();
                        cout << endl;
                        cout << "Enemigos incluidos = " << t.puntosIncluidos(enemigosCentrados) << endl;
                    }
                    
                    if (t.puntosIncluidos(enemigosCentrados) > 0) {
                        // si hay enemigos no es solución y salto a la siguiente iteración
                        continue;
                    } else {
                        // si no hay enemigos, calculo la cantidad de puntos historicos incluidos en el triangulo. Resto 1 porque puntosOrdenados[k] ya
                        // esta sumado en la subsolucion anterior  
                        int nuevosPuntos = t.puntosIncluidos(puntosOrdenados) - 1;
                        
                        if (DEBUG_STATUS){
                            cout << "Nuevos puntos que se incluyen : " << nuevosPuntos << endl;
                        }
                        
                        // si la nueva solucion es mayor entonces la guardamos 
                        if (subsoluciones[z].first + nuevosPuntos > subsoluciones[k].first) {
                            
                            if (DEBUG_STATUS){
                                cout << "Mejora solucion: " << "{" << subsoluciones[k].first << ",";
                                subsoluciones[k].second.imprimir();
                                cout << "} ----> {" << subsoluciones[z].first + nuevosPuntos << ",";
                                puntosOrdenados[z].imprimir();
                                cout << "}";
                            }
                            
                            subsoluciones[k].first = subsoluciones[z].first + nuevosPuntos;
                            subsoluciones[k].second = puntosOrdenados[z];
                        // si es igual nos quedamos con la que menor angulo tenga
                        } else if (subsoluciones[z].first + nuevosPuntos == subsoluciones[k].first) {
                            p1 = puntosOrdenados[z];
                            p2 = subsoluciones[k].second;
                            Punto p3 = centro;
                            p1.restar(puntosOrdenados[k]);
                            p2.restar(puntosOrdenados[k]);
                            p3.restar(puntosOrdenados[k]);
                            double angle1 = acos((p1.getX()*p3.getX()+p1.getY()*p3.getY())/(p1.norma2()*p3.norma2()));
                            double angle2 = acos((p2.getX()*p3.getX()+p2.getY()*p3.getY())/(p2.norma2()*p3.norma2()));   
                            if (angle1 < angle2) {
                                subsoluciones[k].first = subsoluciones[z].first + nuevosPuntos;
                                subsoluciones[k].second = puntosOrdenados[z];
                            }                             
                        }
                    }
                }
            }
            for (int f = 0; f < subsoluciones.size(); f++) {
                if (subsoluciones[f].first > maximo)
                    maximo = subsoluciones[f].first;
            }

            if (DEBUG_STATUS){
                cout << "Subsoluciones: \n";
                cout << "[";
                for (int g = 0; g < subsoluciones.size(); g++)
                {
                    cout << "{" << subsoluciones[g].first << ",";
                    subsoluciones[g].second.imprimir();
                    cout << "}";
                    if (g != subsoluciones.size()-1)
                        cout << ";";
                }
                cout << "]\n";
                cout << "Maximo hasta el momento: " << maximo << endl;  
            }
        }
        if (DEBUG_STATUS) cout << "\n";
    }
    return maximo;
}