#include "funciones.cpp"

int main()
{
  // pair<int, vector< vector<int> > > input = parsearEntrada("entrada1.txt");
  pair<int, vector< vector<int> > > input = parsearStdin();
  
  int res = maximaDiversion(input.first, input.second);
  cout << res << endl;

  return 0;
}