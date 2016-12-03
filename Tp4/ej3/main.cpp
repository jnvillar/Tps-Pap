#include "punto.cpp"
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
// #include <tuple>        // std::tuple
#include <utility>      // std::pair

// Para activar modo debug setear DEBUG_STATUS true
#define DEBUG_STATUS true  

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
    for (int i = 0; i < puntos.size(); i++) {
        if (centro == puntos[i]) {
            puntos.erase(puntos.begin()+i);
            i--;
        } else {
            puntos[i].restar(centro);
        }
    }
    sort(puntos.begin(), puntos.end(), menorAngulo);
    return puntos;
}

vector<Punto> centrar(Punto centro, vector<Punto> puntos) {
    for (int i = 0; i < puntos.size(); i++) {
        puntos[i].restar(centro);
    }
    return puntos;
}

pair < vector<Punto>, vector<Punto> > parsear() {
    // parseo de input por linea de comando
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
            cout << "Puntos ordenados y centrados: \n";
            imprimirPuntos(puntosOrdenados);
            cout << "Puntos enemigos centrados: \n";
            imprimirPuntos(enemigosCentrados);
        }

        // itero sobre puntosOrdenados tomando en cada iteración a la recta (puntosOrdenados[i],puntosOrdenados[j]) como primer lado del polígono 
        for (int j = 0; j < h-1; j++) {
            // construyo un vector para guardar soluciones parciales. Utilizo los ultimos h-1-j elementos del mismo. No utilizo directamente un
            // vector de tamaño h-1-j para no tener que hacer tantas cuentas con los indices a la hora de acceder
            pair<int, Punto> init(2, centro);
            vector< pair<int, Punto> > subsoluciones(h-1, init);
            for (int q = 0; q < j; q++)
            {
                subsoluciones[q].first = 0;
            }
            // itero sobre puntosOrdenados a partir de la posición j+1 y en cada iteracion busco la mejor solución para el subconjunto de puntos incluido en
            // [puntosOrdenados[j+1] ; puntosOrdenados[k]], con la condicion de que dicha solucion incluya al punto puntosOrdenados[k]
            for (int k = j+1; k < h-1; k++) {
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
                            // p1 = puntosOrdenados[z];
                            // p2 = subsoluciones[k].second;
                            // p1.restar(puntosOrdenados[k]);
                            // p2.restar(puntosOrdenados[k]);
                            // pc = p1.prodCruz(p2);
                            if (angle1 < angle2) {
                                subsoluciones[k].first = subsoluciones[z].first + nuevosPuntos;
                                subsoluciones[k].second = puntosOrdenados[z];
                            }                             
                        }
                    }
                }
            }
            for (int i = 0; i < subsoluciones.size(); i++) {
                if (subsoluciones[i].first > maximo)
                    maximo = subsoluciones[i].first;
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

int main()
{
    // Punto p0(1.0, 1.0);
    // Punto p1(-1.0, 2.0);
    // Punto p2(3.0, -5.0);
    // Punto p3(1.0, -3.0);
    // Punto p4(-3.0, -2.0);
    // Punto p5(-5.0, 3.0);
    // Punto p6(4.0, 2.0);
    // Punto p7(-2.0, 5.0);
    // Punto p8(2.0, 3.0);
    // Punto p9(2.0, -1.0);
    // Punto p10(5.0, 6.0);
    // Punto p11(-2.0, -4.0);


    // vector<Punto> myvector;
    // myvector.push_back(p1);
    // myvector.push_back(p2);
    // myvector.push_back(p4);
    // myvector.push_back(p3);
    // myvector.push_back(p0);
    // myvector.push_back(p5);
    // myvector.push_back(p8);
    // myvector.push_back(p11);
    // myvector.push_back(p7);
    // myvector.push_back(p9);
    // myvector.push_back(p6);
    // myvector.push_back(p10);


    
    // cout << "[";
    // for (int i = 0; i < myvector.size(); i++) {
    //     myvector[i].imprimir();
    //     cout << ",";
    // }
    // cout << "]" << endl;

    // sort(myvector.begin(), myvector.end(), menorAngulo);

    // cout << "[";
    // for (int i = 0; i < myvector.size(); i++) {
    //     myvector[i].imprimir();
    //     cout << ",";
    // }
    // cout << "]" << endl;


    // Punto p0(0.0, -2.0);
    // Punto p1(1.0, -2.0);
    // Punto p2(3.0, -2.0);
    // double a = p1.prodCruz(p2);
    // double b = p2.prodCruz(p1);
    
    // cout << "p1 x p2 = " << a << endl;
    // cout << "p2 x p1 = " << b << endl; 

    pair < vector<Punto>, vector<Punto> > parametros = parsear();
    int res = murallaMaxima(parametros.first, parametros.second);
    cout << "Resultado = " << res << endl;

    // Punto p1(-6,0);
    // Punto p2(3,0);
    // Segmento s1(p1, p2, 0, 1);

    // Punto p3(0,4);
    // Punto p4(0,-2);
    // Segmento s2(p3, p4, 0, 1);


    // bool a = s1.hayInterseccion(s2);
    // bool b = s2.hayInterseccion(s1);
    // bool c = s1.hayInterseccion(s1);
    // bool d = s2.hayInterseccion(s2);

    // cout << "s1 con s2: " << a << endl;
    // cout << "s2 con s1: " << b << endl;
    // cout << "s1 con s1: " << c << endl;
    // cout << "s2 con s2: " << d << endl;










}
