#include <vector>
#include <iostream>
#include <tuple>        // std::tuple
#include <sstream>      // std::istringstream
#include <fstream>      // std::ifstream
#include <stdio.h>
#include <string.h>

using namespace std;

tuple< vector<int>, vector< vector<int> >, vector< vector<int> > > parsearStdin();

tuple< vector<int>, vector< vector<int> >, vector< vector<int> > > parsearArchivo(const char* file);

void imprimir_matriz(vector< vector<int> > m);

void construirTablaAditiva(vector< vector<int> > &tabla, const vector< vector<int> > sueldos, int c, int a);

void resolverEjercicio(char* file);