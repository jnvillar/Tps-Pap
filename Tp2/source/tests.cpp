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

	cout<< nodosAlcanzables.size() <<endl;

	/*

	for (int i = 0; i < nodosAlcanzables.size(); i++){
		cout << nodosAlcanzables[i] << endl;		
	}	*/
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