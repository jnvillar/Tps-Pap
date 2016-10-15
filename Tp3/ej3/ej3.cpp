#include <vector>
#include <iostream>

using namespace std;

int construirTablaAditiva(vector< vector<int> >& tabla, const vector< vector<int> >& sueldos)
{
  int c = sueldos.size();
  int a = sueldos[0].size();
  vector<int> fila0(a + 1, 0);
  tabla.push_back(fila0);
  vector<int> filaX(1,0);
  for (int i = 1; i <= c; i++) {
    
  }
}

parsearInput()
{
  int c;
  cin >> c;
  int a;
  cin >> a;
  int q;
  cin >> q;
  vector< vector<int> > valores;
  for (int i = 0; i < c; i++) {
    vector<int> fila;
    for (int j = 0; j < a; j++) {
      int m_ij;
      cin >> m_ij;
      fila.push_back(m_ij);
    }
    valores.push_back(fila);
  }

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


}


int main()
{
  int c;
  cin >> c;
  int a;
  cin >> a;
  int q;
  cin >> q;
  vector< vector<int> > valores;
  for (int i = 0; i < c; i++) {
    vector<int> fila;
    for (int j = 0; j < a; j++) {
      int m_ij;
      cin >> m_ij;
      fila.push_back(m_ij);
    }
    valores.push_back(fila);
  }

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

  vector< vector<int> > tabla;
  construirTablaAditiva(tabla);  
  for (int i = 0; i < q) {
    
  }

}