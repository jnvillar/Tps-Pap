#include "math.h"
#include <iostream>
#include <vector>

using namespace std;

class Punto{
public:
    Punto(){
        coordX = 0;
        coordY = 0;
    }
    Punto(double x, double y){
        coordX = x;
        coordY = y;
    }

    double getX() const {
        return coordX;
    }

    double getY() const {
        return coordY;
    }

    void setX(double x) {
        coordX = x;
    }

    void setY(double y) {
        coordY = y;
    }

    void imprimir() const{
        cout << "(" << coordX << "," << coordY << ")";
    }

    void imprimirComoRes(){
        cout << coordX << " " << coordY;
    }

    void sumar(Punto p){
        coordX += p.getX();
        coordY += p.getY();
    }

    double norma2(){
        return sqrt(coordY*coordY + coordX*coordX);
    }

    void restar(Punto p){
        coordX -= p.getX();
        coordY -= p.getY();
    }

    double distEuclidea(Punto p){
        Punto aux(coordX,coordY);
        aux.restar(p);
        return aux.norma2();
    }

    double prodEscalar(Punto p){
        double x = coordX*p.getX();
        double y = coordY*p.getY();
        return x+y;
    }

    double prodCruz(const Punto &p){
        double x = coordX*p.getY();
        double y = coordY*p.getX();
        return x-y;
    }


    bool operator < ( const Punto& p) const {
        bool res = false;
        if(coordX<p.getX()){
            res = true;
        }
        else if (coordX == p.getX()){
            if(coordY<p.getY()){
                res = true;
            }
        }
        return res;
    }

    bool operator == (const Punto& p) {
        bool res = false;
        if(coordX == p.getX() && coordY == p.getY()){
            res = true;
        }
        return res;
    }
    
    // T& T::operator =(const T2& b);
    void operator = (const Punto& p) {
        coordX = p.getX();
        coordY = p.getY();
    }

private:
    double coordX;
    double coordY;
};

Punto min(Punto p1, Punto p2){
    if(p1<p2){
        return p1;
    }
    return p2;
}

Punto max(Punto p1, Punto p2){
    if(p1<p2){
        return p2;
    }
    return p1;
}

// class Recta{
// public:

//     Recta(Punto direc, Punto p){
//         direccion = direc;
//         punto = p;
//     }

//     Punto getDireccion() const{
//         return direccion;
//     }

//     Punto getPunto() const{
//         return punto;
//     }

//     bool hayInterseccion(Recta r) {
//         bool res = true;
//         if (direccion.prodCruz(r.getDireccion()) == 0)
//             res = false;
//         return res;
//     }

// private:
//     Punto direccion;
//     Punto punto;
// };

class Segmento{
public:

    Segmento(Punto direc, Punto p, double tmin, double tmax){
        direccion = direc;
        punto = p;
        tminimo = tmin;
        tmaximo = tmax;
    }

    Punto getDireccion() const{
        return direccion;
    }

    Punto getPunto() const{
        return punto;
    }

    double getTminimo() const{
        return tminimo;
    }

    double getTmaximo() const{
        return tmaximo;
    }

    bool hayInterseccion(Segmento s) {
        bool res;
        int denom1 = direccion.prodCruz(s.getDireccion());
        int denom2 = s.getDireccion().prodCruz(direccion);
        if (denom1 == 0) {
            res = false;
        } else {
            Punto puntoS = s.getPunto();
            puntoS.restar(punto);
            int num1 = puntoS.prodCruz(s.getDireccion());
            double alpha = (double) num1 / (double) denom1;
            puntoS = punto;
            puntoS.restar(s.getPunto());
            int num2 = puntoS.prodCruz(direccion);
            double beta = (double) num2 / (double) denom2;
            if (alpha >= tminimo && alpha <= tmaximo && beta >= s.getTminimo() && beta <= s.getTmaximo()) {
                res = true;
            } else {
                res = false;
            }
        }
        return res;
    }

private:
    Punto direccion;
    Punto punto;
    double tminimo;
    double tmaximo;
};


class Triangulo {
public:

    Triangulo(Punto p1, Punto p2, Punto p3) {
        puntoUno = p1;
        puntoDos = p2;
        puntoTres = p3;
    }

    Punto getPuntoUno() const{
        return puntoUno;
    }

    Punto getPuntoDos() const{
        return puntoDos;
    }

    Punto getPuntoTres() const{
        return puntoDos;
    }

    int puntosIncluidos(vector<Punto> puntos) {
        int incluidos = 0;
        int size = puntos.size();
        for (int i = 0; i < size; i++) {
            if (puntos[i] == puntoUno || puntos[i] == puntoDos || puntos[i] == puntoTres) {
                incluidos++;
            } else {
                Punto puntoAfuera(1200, 1200);
                puntoAfuera.restar(puntos[i]);
                Segmento s(puntoAfuera, puntos[i], 0, 1);
                Punto d1 = puntoUno;
                d1.restar(puntoDos);
                Segmento lado1(d1, puntoDos, 0, 1);
                Punto d2 = puntoUno;
                d2.restar(puntoTres);
                Segmento lado2(d2, puntoTres, 0, 1);
                Punto d3 = puntoDos;
                d3.restar(puntoTres);
                Segmento lado3(d3, puntoTres, 0, 1);
                int intersecciones = 0;
                if (s.hayInterseccion(lado1))
                    intersecciones++;
                if (s.hayInterseccion(lado2))
                    intersecciones++;
                if (s.hayInterseccion(lado3))
                    intersecciones++;
                if (intersecciones == 1)
                    incluidos++;
            }            
        }
        return incluidos;
    }

private:
    Punto puntoUno;
    Punto puntoDos;
    Punto puntoTres;

};