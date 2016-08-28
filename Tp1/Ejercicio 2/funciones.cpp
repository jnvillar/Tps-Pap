#include "funciones.h"

/**
 * archivo es el nombre del archivo que queremos parsear
 */
pair<int, vector< vector<int> > > parsearEntrada(string archivo)
{
  int debug = 0; //debug != 0 muestra lo que se parsea

  const char* file = archivo.c_str();
  pair<int, vector< vector<int> > > res;
  string line;
  ifstream myfile(file);
  if (myfile.is_open())
  {
    istringstream iss;
    getline(myfile, line);
    iss.str(line);
    int cantAmigas;
    iss >> cantAmigas;
    if (debug) cout << "Cantidad de amigas: " << cantAmigas << " \n"; 

    if (debug) cout << "Matriz de diversion:\n"; 
    vector < vector<int> > diversionAmigas;
    iss.clear();
    while (getline(myfile, line))
    {
      vector<int> filaDiversionAmigas; 
      iss.str(line);
      int value;
      while (iss >> value)
      {
        if (debug) cout << value << " "; 
        filaDiversionAmigas.push_back(value);
      }
      if (debug) cout << "\n"; 
      diversionAmigas.push_back(filaDiversionAmigas);
      iss.clear();
    }
   
    myfile.close();
    res.first = cantAmigas;
    res.second = diversionAmigas; 
  }
  else cout << "No se pudo abrir el archivo " << archivo << "\n"; 
  return res;
}

/**
 * cantAmigas es el número de amigas
 * diversionAmigas es la matriz que contiene la diversión que aporta la relación entre cada par de amigas. Esta matriz debe ser cuadrada de tamaño cantAmigas x cantAmigas, simétrica y con ceros en la diagonal.  
 */
int maximaDiversion(int cantAmigas, vector< vector<int> > diversionAmigas)
{
  // inicializamos las estructuras donde vamos a ir guardando información
  vector<int> diversionFiestas (1 << cantAmigas, -1);
  vector<int> diversionMaxima (1 << cantAmigas, -1);
  diversionFiestas[0] = 0;
  diversionMaxima[0] = 0;
  
  // calculamos la diversion para cada subconjunto de amigas, suponiendo que el subconjunto es una fiesta
  for (int i = 1; i < diversionFiestas.size(); i++)
  {
    int diversion = calcularDiversion(cantAmigas, i, diversionAmigas);
    diversionFiestas[i] = diversion;
  }  

  return maximaDiversionAux(cantAmigas, (1 << cantAmigas) - 1, diversionAmigas, diversionFiestas, diversionMaxima);
}

/**
 * n es el número de amigas inicial; lo usamos para la función calcularDiversion
 * mask es una máscara de bits que representa el subconjunto de amigas de interés 
 * diversionAmigas es la matriz que contiene la diversión que aporta la relación entre cada par de amigas. Esta matriz debe ser cuadrada de tamaño cantAmigas x cantAmigas, simétrica y con ceros en la diagonal.
 * diversionFiestas contiene para cada subconjunto de amigas la diversión que suman si todas están juntas en la misma fiesta (inicialmente comienza lleno de -1, pero se va completando a medida que se ejecuta el algoritmo)
 * diversionMaxima contiene para cada subconjunto de amigas, la máxima diversión que se puede obtener oranizando a las amigas en una o mas fiestas de alguna forma (inicialmente comienza lleno de -1, pero se va completando a medida que se ejecuta el algoritmo).
 */
int maximaDiversionAux(int n, int mask, const vector< vector<int> >& diversionAmigas, vector<int>& diversionFiestas, vector<int>& diversionMaxima)
{
  int debug = 0; //debug != 0 muestra las llamadas recursivas

  // verificamos si ya calculamos este resultado previamente, y si es asi lo devolvemos
  if (diversionMaxima[mask] != -1)
    return diversionMaxima[mask];

  // asignamos a res un valor inicial negativo ya que cualquier solución parcial va a ser mayor
  int res = -1;
  
  // iteramos sobre todos los subconjuntos de mask y si tienen diversion >= 0 llamamos recursivamente a la funcion
  for (int i = mask; i != 0; i = mask & (i - 1))
  {
    if (diversionFiestas[i] >= 0)
    {
      if (debug)
      {
        int aux = mask^i;
        cout << "i = " << i << " Diversion = " << diversionFiestas[i] << "\n"; 
        cout << "Llamada recursiva: maximaDiversionAux(" << n << ", " << aux << ", diversionAmigas, diversionFiestas)\n";
      } 
      res = max(res, maximaDiversionAux(n, mask^i, diversionAmigas, diversionFiestas, diversionMaxima) + diversionFiestas[i]);
    }
  }

  // guardamos en diversionMaxima el resultado calculado para poder utilizarlo en otra llamada si es necesario
  diversionMaxima[mask] = res;
  return res;
}

/**
 * n es el número de amigas inicial
 * mask es una máscara de bits que representa el subconjunto de amigas de interés 
 * diversionAmigas es la matriz que contiene la diversión que aporta la relación entre cada par de amigas. Esta matriz debe ser cuadrada de tamaño cantAmigas x cantAmigas, simétrica y con ceros en la diagonal. 
 */
int calcularDiversion(int n, int mask, const vector< vector<int> >& diversionAmigas)
{
  // decodificamos la máscara de bits. Para ello vamos 'prendiendo' un bit distinto en i en cada iteración y hacemos un '&' para saber si esa amiga esta incluida en el subconjunto de interés o no 
  int i = 1 << (n - 1);
  int amiga = n - 1;
  vector<int> amigas;

  while (i > 0)
  {
    if ((mask & i) > 0) 
      amigas.push_back(amiga);
    amiga--;
    i = i >> 1;
  }

  // una vez que interpretamos la máscara, calculamos la diversión
  int res = 0;
  int size = amigas.size();
  for (i = 0; i < size; i++)
  {
    for (int j = i + 1; j < size; j++)
    {
      res += diversionAmigas[amigas[i]][amigas[j]];
    }
  }
  
  return res;
}