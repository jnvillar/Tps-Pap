#include <iostream>
#include "parser.cpp"
#include <vector>
#include <map>
#include <set>


using namespace std;

set<Recta> conjRecta;
map<Punto,set<Recta> > puntoRectas;
vector<Punto> res;
Punto puntoInicial;
int lados;

void imprimirSetRectas(set<Recta> &conjRecta){
    cout << "Imprimiendo set de rectas:" << endl;
    for (set<Recta>::iterator i = conjRecta.begin(); i!=conjRecta.end();i++) {
        i->imprimir();
    }
}

void imprimirDicRectas(map<Punto,set<Recta> > &puntoRectas ){
    cout << "Imprimiendo diccionario de puntos y rectas:" << endl;
    for (map<Punto,set<Recta> >::iterator i = puntoRectas.begin(); i!=puntoRectas.end();i++) {
        cout << "Punto ";
        i->first.imprimir();
        imprimirSetRectas(i->second);
    }
}

void getOtroPuntoRecta(Punto &p,Recta const &r, Punto &res){
    Punto PrimerPunto = r.getPuntoUno();
    Punto SegundoPunto = r.getPuntoDos();
    if(p == PrimerPunto){
        res = SegundoPunto;
    }
    else{
        res = PrimerPunto;
    }
}

Punto elejirDireccion(){
    // Obtengo los lados a los que pertenece el punto incial
    set<Recta> rectasPuntoInicial = puntoRectas[puntoInicial];
    // Obtengo los dos lados del poligono a los que pertenece el punto inicial
    set<Recta>::iterator recta1 = rectasPuntoInicial.begin();
    set<Recta>::iterator recta2 = rectasPuntoInicial.begin();recta2++;

    // Obtengo los dos vertices vecinos del punto inicial
    Punto p1; getOtroPuntoRecta(puntoInicial,*recta1,p1);
    Punto p2; getOtroPuntoRecta(puntoInicial,*recta2,p2);

    // Normalizo Puntos para luego hacer el producto cruz
    Punto p1Normalizado = p1.restar(puntoInicial);
    Punto p2Normalizado = p2.restar(puntoInicial);

    // Calculo el producto cruz
    double prodCruz = p1Normalizado.prodCruz(p2Normalizado);

    if(prodCruz<0){
        // Si dio negativo, p1 era el vertice siguiente en sentido horario
        return p1;
    }else{
        // Si dio positivo, entonces era el vertice siguiente en sentido antihorario
        return p2;
    }
}
void getOtraRecta(Punto &p1,Punto &p2, Recta &rectaSiguiente) {
    set<Recta> rectas = puntoRectas[p1];
    set<Recta>::iterator recta1 = rectas.begin();
    set<Recta>::iterator recta2 = rectas.begin();recta2++;

    if(recta1->contieneAlPunto(p1) && recta1->contieneAlPunto(p2)){
        Recta aux = *recta2;
        rectaSiguiente =  aux;
    }
    else{
        Recta aux = *recta1;
        rectaSiguiente =  aux;
    }
}




int main() {
    // Parseo info
    parser(conjRecta,puntoRectas,lados,puntoInicial);
    // Agrego el primer punto (menor coordenada x, desempatando por y)
    res.push_back(puntoInicial);

    // Obtengo el vertice siguiente, utilizando el producto cruz entre los dos vertices vecinos del punto inicial
    Punto puntoSiguiente = elejirDireccion();
    Recta rectaSiguiente;
    Punto puntoAnterior = puntoInicial;

    while(!(puntoSiguiente==puntoInicial)) { // Mientras no llegue al vertice inicial
        // Agrego el vertice al que avance al resultado
        res.push_back(puntoSiguiente);
        // Veo los lados a los que pertenece el vertice siguiente y obtengo el lado del poligono
        // que contiene al vertice al que avance y que no contiene al vertice anterior a ese
        getOtraRecta(puntoSiguiente,puntoAnterior,rectaSiguiente);
        // El vertice que habia avanzado es ahora el vertice viejo, actualizo la variable
        puntoAnterior = puntoSiguiente;
        // Obtengo el vertice siguiente viendo los vertices que contiente el lado del poligono
        // conseguido anteriormente. Me quedo con el vertice que es distinto a los dos ultimos visitados
        getOtroPuntoRecta(puntoSiguiente,rectaSiguiente, puntoSiguiente); // Esta funcion actualiza el siguiente
    }

    // Imprimo solucion en el formato pedido
    for (int i = 0; i < res.size(); ++i) {
        res[i].imprimirComoRes();
        if(i!=res.size()-1){
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}