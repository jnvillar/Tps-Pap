#include "funciones.cpp"

int main()
{
    pair < vector<Punto>, vector<Punto> > parametros = parsear();
    int res = murallaMaxima(parametros.first, parametros.second);
    cout << "Resultado = " << res << endl;
}