#include "funciones.cpp"

int main()
{
  pair<int, vector< vector<int> > > input = parsearEntrada("entrada1.txt");
  
  int res1 = maximaDiversion(input.first, input.second);
  cout << res1 << endl;

  input = parsearEntrada("entrada2.txt");

  int res2 = maximaDiversion(input.first, input.second);
  cout << res2 << endl;

  input = parsearEntrada("entrada3.txt");

  int res3 = maximaDiversion(input.first, input.second);
  cout << res3 << endl;

  input = parsearEntrada("entrada4.txt");

  int res4 = maximaDiversion(input.first, input.second);
  cout << res4 << endl;

  return 0;
}