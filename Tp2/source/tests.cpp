void testDfs(){
	Grafo prueba(3);
	prueba.agregarArista(0,1);
	prueba.agregarArista(1,2);
	prueba.agregarArista(2,0);

	vector<int> nodosAlcanzables;
	nodosAlcanzables = prueba.dfs(2);

	for (int i = 0; i < nodosAlcanzables.size(); i++){
		cout << nodosAlcanzables[i] << endl;		
	}	
}

void testBfs(){
	Grafo prueba(3);
	prueba.agregarArista(0,1);
	prueba.agregarArista(1,2);
	prueba.agregarArista(2,0);

	vector<int> nodosAlcanzables;
	nodosAlcanzables = prueba.bfs(2);

	for (int i = 0; i < nodosAlcanzables.size(); i++){
		cout << nodosAlcanzables[i] << endl;		
	}	
}

void testInvertir(){
	Grafo prueba(3);
	prueba.agregarArista(0,1);
	prueba.agregarArista(0,2);
	prueba.imprimirGrafo();
	cout << "listo" << endl;
	prueba.invertirAristas();
	prueba.imprimirGrafo();
}

void testOrdenKosaraju(){
	Grafo prueba(11);
	prueba.agregarArista(0,1);
	prueba.agregarArista(1,2);
	prueba.agregarArista(2,0);
	prueba.agregarArista(1,3);
	prueba.agregarArista(3,4);
	prueba.agregarArista(4,5);
	prueba.agregarArista(5,3);
	prueba.agregarArista(6,5);
	prueba.agregarArista(6,7);
	prueba.agregarArista(7,8);
	prueba.agregarArista(8,9);
	prueba.agregarArista(9,6);
	prueba.agregarArista(9,10);

	stack<int> ordKosaraju;
	ordKosaraju = prueba.ordenKosaraju();	
	
	while(!ordKosaraju.empty()){
			cout << ordKosaraju.top() << endl;		
			ordKosaraju.pop();
	}	
}


void testKosaraju1a(){
	Grafo prueba(11);
	prueba.agregarArista(0,1);
	prueba.agregarArista(1,2);
	prueba.agregarArista(2,0);
	prueba.agregarArista(1,3);
	prueba.agregarArista(3,4);
	prueba.agregarArista(4,5);
	prueba.agregarArista(5,3);
	prueba.agregarArista(6,5);
	prueba.agregarArista(6,7);
	prueba.agregarArista(7,8);
	prueba.agregarArista(8,9);
	prueba.agregarArista(9,6);
	prueba.agregarArista(9,10);

	
	vector<vector<int> > res = prueba.kosaraju2();

	for (int i = 0; i < res.size(); i++){
			cout << "Componente: " << i << endl;
			for (int j = 0; j < res[i].size(); j++){
				cout << res[i][j]  << " " << endl;
			}
			cout << endl;
		}		
}

void testKosaraju1b(){
	Grafo prueba(11);
	prueba.agregarArista(0,1);
	prueba.agregarArista(1,2);
	prueba.agregarArista(2,0);
	prueba.agregarArista(1,3);
	prueba.agregarArista(3,4);
	prueba.agregarArista(4,5);
	prueba.agregarArista(5,3);
	prueba.agregarArista(6,5);
	prueba.agregarArista(6,7);
	prueba.agregarArista(7,8);
	prueba.agregarArista(8,9);
	prueba.agregarArista(9,6);
	prueba.agregarArista(9,10);

	
	vector<int> compConex = prueba.kosaraju();

	for (int i = 0; i < compConex.size(); i++){
			cout << "Nodo: " << i << " Componente: "<< compConex[i] << endl;		
	}
	
}


