#include "ej3.h"

// Para activar modo debug setear DEBUG_STATUS true
#define DEBUG_STATUS false

tuple< vector<int>, vector< vector<int> >, vector< vector<int> > > parsearStdin() {
  // parseo de input por linea de comando
  bool debug = DEBUG_STATUS;
    
  // parseo c  
  int c;
  cin >> c;
  if (debug) cout << "C: " << c << " \n"; 

  // parseo a
  int a;
  cin >> a;
  if (debug) cout << "A: " << a << " \n"; 
  
  // parseo q
  int q;
  cin >> q;
  if (debug) cout << "Q: " << q << " \n"; 
  
  vector<int> caq;
  caq.push_back(c);
  caq.push_back(a);
  caq.push_back(q);
  
  // parseo sueldos
  vector< vector<int> > sueldos;
  for (int i = 0; i < c; i++) {
    vector<int> fila;
    for (int j = 0; j < a; j++) {
      int m_ij;
      cin >> m_ij;
      fila.push_back(m_ij);
    }
    sueldos.push_back(fila);
  }

  if (debug) {
    cout << "Sueldos: \n";
    imprimir_matriz(sueldos);
  }

  // parseo queries
  vector< vector<int> > queries; 
  for (int i = 0; i < q; i++) {
    vector<int> query;
    for (int j = 0; j < 4; j++) {
      int q_ij; 
      cin >> q_ij;
      query.push_back(q_ij);
    }
    queries.push_back(query);
  }

  if (debug) {
    cout << "Queries: \n";
    imprimir_matriz(queries);
  }

  tuple < vector<int>, vector< vector<int> >, vector< vector<int> > > res(caq, sueldos, queries);
  return res;
}

tuple< vector<int>, vector< vector<int> >, vector< vector<int> > > parsearArchivo(const char* file) {
  // parseo de input desde archivo  
  bool debug = DEBUG_STATUS;
  vector<int> caq;
  vector< vector<int> > sueldos;
  vector< vector<int> > queries;

  string line;
  ifstream myfile(file);
  if (myfile.is_open()) {
    istringstream iss;
    getline(myfile, line);
    iss.str(line);
    // parseo c
    int c;
    iss >> c;
    if (debug) cout << "C: " << c << " \n"; 
    // parseo a
    int a;
    iss >> a;
    if (debug) cout << "A: " << a << " \n";
    // parseo q
    int q;
    iss >> q;
    if (debug) cout << "Q: " << q << " \n"; 
    caq.push_back(c);
    caq.push_back(a);
    caq.push_back(q);

    // parseo sueldos
    iss.clear();
    int i = 0;
    while (i < c && getline(myfile, line)) {
      vector<int> fila; 
      iss.str(line);
      int value;
      
      while (iss >> value)
        fila.push_back(value);
      
      sueldos.push_back(fila);
      iss.clear();
      i++;
    }
    if (debug) {
      cout << "Sueldos:\n";
      imprimir_matriz(sueldos); 
    }

    // parseo queries
    iss.clear();
    while (getline(myfile, line)) {
      vector<int> query; 
      iss.str(line);
      int value;
      
      while (iss >> value)
        query.push_back(value);
      
      queries.push_back(query);
      iss.clear();
    }
    if (debug) {
      cout << "Queries:\n";
      imprimir_matriz(queries); 
    }
   
    myfile.close();
  }
  else cout << "No se pudo abrir el archivo " << file << "\n"; 
  
  tuple < vector<int>, vector< vector<int> >, vector< vector<int> > > res(caq, sueldos, queries);
  return res;
}

void imprimir_matriz(vector< vector<int> > m) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++)
      cout << m[i][j] << " ";
    cout << endl;    
  }
}

void construirTablaAditiva(vector< vector<int> > &tabla, const vector< vector<int> > sueldos, int c, int a) {
  
  // construyo tabla vacia
  tabla.resize(c+1);
  for (int i = 0; i < c+1; i++) {
    tabla[i].resize(a+1);
  }

  // lleno de ceros primer columna
  for (int i = 0; i < c+1; i++) {
    tabla[i][0] = 0;
  }

  // lleno de ceros primera fila
  for (int j = 1; j < a+1; j++) {
    tabla[0][j] = 0;
  }

  // lleno el resto de la tabla utilizando los valores calculados en iteraciones anteriores
  for (int i = 0; i < c; i++) {
    for (int j = 0; j < a; j++) {
      tabla[i+1][j+1] = sueldos[i][j] + tabla[i][j+1] + tabla[i+1][j] - tabla[i][j];
    }
  }
}

void resolverEjercicio(char* file) {

  bool debug = DEBUG_STATUS;

  tuple< vector<int>, vector< vector<int> >, vector< vector<int> > > args;
  
  if (strcmp(file, ""))
    args = parsearArchivo(file);
  else
    args = parsearStdin();

  int c = get<0>(args)[0];
  int a = get<0>(args)[1];
  int q = get<0>(args)[2];

  vector< vector<int> > sueldos = get<1>(args);
  vector< vector<int> > queries = get<2>(args); 

  vector< vector<int> > tabla;
  construirTablaAditiva(tabla, sueldos, c, a);  
  
  if (debug) {
    cout << "Tabla aditiva: \n";
    imprimir_matriz(tabla);
  }

  // obtengo resultados buscados a partir de la tabla aditiva
  for (int i = 0; i < q; i++) {
    int c_1 = queries[i][0];
    int a_1 = queries[i][1];
    int c_2 = queries[i][2];
    int a_2 = queries[i][3];
    int query_i = tabla[c_2][a_2] - tabla[c_1][a_2] - tabla[c_2][a_1] + tabla[c_1][a_1];     

    // cout << "query_" << i << " = " << tabla[c_2][a_2] << " - " << tabla[c_1][a_2] << " - " << tabla[c_2][a_1] << " + " << tabla[c_1][a_1] << " = " << query_i << endl;     
    cout << query_i << endl;
  }
}