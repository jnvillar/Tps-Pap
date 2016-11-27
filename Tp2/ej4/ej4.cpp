#include "parser.cpp"
//#include "tests.cpp"
using namespace std;

int main(int argc, char const *argv[])
{

	vector<pair<int,int> > preguntas;
	Grafo grafo = parser(preguntas);
	vector<int> respuestas = grafo.kosaraju();

	for (int i = 0; i < preguntas.size(); i++){
		if (respuestas[preguntas[i].first] == respuestas[preguntas[i].second]){
			cout << "S" << endl;
		}else{
			cout << "N" << endl;
		}
	}
	return 0;
}