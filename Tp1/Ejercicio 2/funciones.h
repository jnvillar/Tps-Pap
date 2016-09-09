#include <utility>      // std::pair, std::make_pair
#include <vector>       // std::vector
#include <algorithm>    // std::max
#include <fstream>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::istringstream
using namespace std;

pair<int, vector< vector<int> > > parsearArchivo(string archivo);

pair<int, vector< vector<int> > > parsearStdin();

int maximaDiversion(int cantAmigas, vector< vector<int> > diversionAmigas);

int maximaDiversionAux(int n, int mask, const vector< vector<int> >& diversionAmigas, vector<int>& diversionFiestas, vector<int>& diversionMaxima);

int calcularDiversion(int n, int mask, const vector< vector<int> >& diversionAmigas);

