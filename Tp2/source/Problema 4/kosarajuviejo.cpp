

		bool vecinosSinVisitar(Vady vecinos, vector<bool> &visitados){
			for(int i = 0; i < vecinos.size(); i++){
				if (visitados[vecinos[i].nodo()] == false){
					return true;
				} 
			}
			return false;
		}

		unsigned int damePrimSinVisitar(Vady vecinos, vector<bool> &visitados){
			for(int i = 0; i < vecinos.size(); i++){
				if (visitados[vecinos[i].nodo()] == false){
					return vecinos[i].nodo();
				} 
			}
		}

		unsigned int dameSinVistar(vector<bool> &visitados){
			for(unsigned int i = 0; i < visitados.size(); i++){
				if (visitados[i] == false){
					return i;
				} 
			}				
		}

		bool haySinVisitar(vector<bool> &visitados){
			for(unsigned int i = 0; i < visitados.size(); i++){
				if (visitados[i] == false){
					return true;
				} 
			}
			return false;
		}


		GrafoListaAdy darVueltaAristas(){
			pair<int,int> aux;
			aux.first = 0;
			aux.second = 0;
			vector< pair<int,int> > n(_cantNodos,aux);
			GrafoListaAdy res = GrafoListaAdy(n);
			for(unsigned int i= 0; i<_cantNodos;i++){
				for(unsigned int j=0; j<_graf[i].size(); j++){
					res.agregarAristaRapidaDirigida( _graf[i][j].nodo(), i);            //AAAAAAAAAAAAAAAAA OBSERVACION, HAY Q HACER Q SE AGREGUEN PARA UN LADO NOMAS AAAAAAAAAAAAAAAAAAA
				}
			}
			return res;
		}

		void dfs(unsigned int nod, vector<bool> &visitados, vector<bool> &enlapila, stack<unsigned int> &compconex, stack<unsigned int> &pila){	
		
			if(enlapila[nod] == true){
				pila.pop();
				return;
			}

			visitados[nod] = true;		
			Vady vecinos = adyacentes(nod);					

			if(!vecinosSinVisitar(vecinos, visitados)){
				enlapila[nod] = true;				
				compconex.push(nod);
				pila.pop();
				return;
			}else{
				for(int i = 0; i < vecinos.size(); ++i){
					if(!visitados[vecinos[i].nodo()]) {
						
						pila.push(vecinos[i].nodo());
					}
				}
				while(!pila.empty()){
					unsigned int nod2 = pila.top();
					dfs(nod2,visitados,enlapila,compconex, pila);				
				}	
			}
		}



		void dfs2(unsigned int nod, vector<bool> &visitados,  vector<bool> &enlapila, vector<unsigned int> &compconex, stack<unsigned int> &pila){	
			
			if(enlapila[nod] == true){
				pila.pop();
				return;
			}

			visitados[nod] = true;		
			Vady vecinos = adyacentes(nod);					

			if(!vecinosSinVisitar(vecinos, visitados)){				
				compconex.push_back(nod);
				pila.pop();
				return;
			}else{
				for(int i = 0; i < vecinos.size(); ++i){
					if(!visitados[vecinos[i].nodo()]) {
						visitados[vecinos[i].nodo()] = true;
						pila.push(vecinos[i].nodo());
					}
				}
				while(!pila.empty()){
					unsigned int nod2 = pila.top();
					dfs2(nod2,visitados,enlapila,compconex, pila);				
				}	
			}
		}


		vector< vector<unsigned int> > kosaraju(){

			stack<unsigned int> compconex;
			vector<bool> visitados(_cantNodos, false);
			vector<bool> enlapila(_cantNodos, false);
			stack<unsigned int> pila;
			unsigned int nod;
			while(haySinVisitar(visitados)){				
				nod = dameSinVistar(visitados);				
				pila.push(nod);				
				dfs(nod, visitados, enlapila, compconex, pila);				
			}
			
			GrafoListaAdy dadovuelta = darVueltaAristas();			
			vector< vector<unsigned int> > res;
			vector<bool> visitados2(_cantNodos, false);	
			vector<bool> enlapila2(_cantNodos, false);

			while(!compconex.empty()){
				if(!visitados2[compconex.top()]){
					unsigned int nod = compconex.top();
					compconex.pop();					
					stack<unsigned int> pila2;
					vector<unsigned int> compofuerconex;
					pila2.push(nod);
					dadovuelta.dfs2(nod, visitados2,enlapila2, compofuerconex,pila2);
					res.push_back(compofuerconex);									
				}else{
					compconex.pop(); 
				}
			}

			for (int i = 0; i < res.size(); i++)
			{
				for (int j = 0; j< res[i].size(); ++j)
				{
					_compconex[j] = i;
				}
			}






		return res;
		}