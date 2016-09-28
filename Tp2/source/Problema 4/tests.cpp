# include "../grafo.cpp" 

using namespace std;

void test(){
	Grafo prueba(12);
	prueba.agregarArista(0,1);
	prueba.agregarArista(1,2);
	prueba.agregarArista(2,0);
	prueba.agregarArista(2,3);	
	prueba.agregarArista(2,6);
	prueba.agregarArista(3,4);
	prueba.agregarArista(4,5);
	prueba.agregarArista(5,3);	
	prueba.agregarArista(5,9);
	prueba.agregarArista(6,7);	
	prueba.agregarArista(7,8);
	prueba.agregarArista(8,6);	
	prueba.agregarArista(8,9);
	prueba.agregarArista(9,10);
	prueba.agregarArista(10,11);
	prueba.agregarArista(11,10);

	vector<pair<int,int> > preguntas;	
	vector<int> respuestas = prueba.kosaraju();

	pair<int,int> p1(0,2);
	pair<int,int> p2(2,3);
	pair<int,int> p3(5,8);
	pair<int,int> p4(9,0);

	preguntas.push_back(p1);
	preguntas.push_back(p2);
	preguntas.push_back(p3);
	preguntas.push_back(p4);

	

	for (int i = 0; i < preguntas.size(); i++){
		if (respuestas[preguntas[i].first] == respuestas[preguntas[i].second]){	
			cout << "S" << endl;
		}else{
			cout << "N" << endl;
		}
	}
	
}