#include "math.h"

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

    void setX(int x) {
        coordX = x;
    }

    void setY(int y) {
        coordY = y;
    }

    void imprimir() const{
        cout << "(" << coordX << "," << coordY << ")" << endl;
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

    Punto restar(Punto p){
        Punto res(coordX-p.getX(),coordY-p.getY());
        return res;
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

    double prodCruz(Punto &p){
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

    bool operator == ( Punto& p) {
        bool res = false;
        if(coordX == p.getX() && coordY == p.getY()){
            res = true;
        }
        return res;
    }

    void operator = ( Punto& p) {
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

class Recta{
public:

    Recta(Punto p1, Punto p2){
        puntoUno = p1;
        puntoDos = p2;
    }

    Recta(){
        Punto p1; Punto p2;
        puntoUno = p1;
        puntoDos = p2;
    }

    Punto getPuntoUno() const{
        return puntoUno;
    }

    Punto getPuntoDos() const{
        return puntoDos;
    }

    bool contieneAlPunto(Punto p)const{
        if (p.getX() == puntoUno.getX() && p.getY() == puntoUno.getY()){
            return true;
        }
        if (p.getX() == puntoDos.getX() && p.getY() == puntoDos.getY()){
            return true;
        }
        return false;
    }

    void imprimir() const{
        cout << "{";
        cout << "(" << puntoUno.getX() << "," << puntoUno.getY() << ")";
        cout << "," ;
        cout << "(" << puntoDos.getX() << "," << puntoDos.getY() << ")";
        cout << "}" << endl;
    }

    bool operator < (const Recta& r) const {
        bool res = false;
        Punto maxR1 = max(puntoUno,puntoDos);
        Punto maxR2 = max(r.getPuntoUno(),r.getPuntoDos());
        Punto minR1 = min(puntoUno,puntoDos);
        Punto minR2 = min(r.getPuntoUno(),r.getPuntoDos());

        if (minR1<minR2){
            return true;
        }
        else if(minR1 == minR2){
            if(maxR1<maxR2){
                return true;
            }
        }
        return false;
    }

    bool operator == (Recta& r) {
        bool res = false;
        Punto p1 = r.getPuntoUno();
        Punto p2 = r.getPuntoDos();

        if( puntoUno == p1 && puntoDos == p2){
            res = true;
        }
        else if(puntoDos == p1 && puntoUno == p2){
            res = true;
        }
        return res;
    }

    void operator = (Recta& r) {
        Punto p1 = r.getPuntoUno(); Punto p2 = r.getPuntoDos();
        puntoUno = p1; puntoDos = p2;
    }

private:
    Punto puntoUno;
    Punto puntoDos;
};