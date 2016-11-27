#include "punto.cpp"
#include <vector>
#include <set>
#include <map>
#include <iostream>

using namespace std;

void reemplazarMinimo(Punto &p, Punto &min ) {
    if(p.getX()<min.getX()) {
        min = p;
    } else if(p.getX()==min.getX()) {
        if(p.getY()< min.getY()) {
            min = p;
        }
    }
}

bool puntoInicialNoDefinido = true;

void parser(set<Recta>& conjRectas,  map<Punto,set<Recta> >& puntoRectas, int& lados, Punto &puntoInicial){
    cin >> lados;
    for (int i = 0; i < lados - 2; ++i) {
        double x; double y;
        // Guardo punto 1
        cin >> x; cin >> y;
        Punto p1(x,y);
        if(puntoInicialNoDefinido) puntoInicial = p1;
        // Guardo punto 2
        cin >> x; cin >> y;
        Punto p2(x,y);
        // Guardo punto 3
        cin >> x; cin >> y;
        Punto p3(x,y);

        reemplazarMinimo(p1,puntoInicial);
        reemplazarMinimo(p2,puntoInicial);
        reemplazarMinimo(p3,puntoInicial);
        // Creo las 3 rectas del triangulo y las guardo en un vector
        Recta r1(p1,p2);
        Recta r2(p2,p3);
        Recta r3(p1,p3);
        vector<Recta> rectasAgregar = {r1,r2,r3};

        // Me quedo con las rectas que no sean repetidas
        for (int j = 0; j < 3; ++j) { // Si no esta lo agrego
            if(conjRectas.count(rectasAgregar[j]) == 0){
                conjRectas.insert(rectasAgregar[j]);
                // Relaciono punto 1 con su recta
                if (puntoRectas.find(rectasAgregar[j].getPuntoUno())==puntoRectas.end()){ //Si no esta, lo defino
                    puntoRectas[rectasAgregar[j].getPuntoUno()] = set<Recta>{rectasAgregar[j]};
                }
                else{
                    puntoRectas[rectasAgregar[j].getPuntoUno()].insert(rectasAgregar[j]); // Esta definido, lo agrego
                }
                // Relaciono punto 2 con su recta
                if (puntoRectas.find(rectasAgregar[j].getPuntoDos())==puntoRectas.end()){ // Si no esta, lo defino
                    puntoRectas[rectasAgregar[j].getPuntoDos()] = set<Recta>{rectasAgregar[j]};
                }else{
                    puntoRectas[rectasAgregar[j].getPuntoDos()].insert(rectasAgregar[j]); // Esta definido, lo agrego
                }
            }else{ // Elimino lo repetido
                conjRectas.erase(rectasAgregar[j]);
                puntoRectas[rectasAgregar[j].getPuntoUno()].erase(rectasAgregar[j]);
                puntoRectas[rectasAgregar[j].getPuntoDos()].erase(rectasAgregar[j]);

            }
        }
    }
}