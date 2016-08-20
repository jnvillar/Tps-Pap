#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int debug = 0;

int sumaMax(vector<int> v){
	
	int max = 0;
	int sumaActual = 0;
	int inicio = 0;
	int actual = 0;

	for (int i = 0; i < v.size(); ++i){

		if(debug){cout << "Iteracion: " << i << endl;}
		int aux = sumaActual;
		if(debug){cout << "Suma Actual: " << sumaActual << endl;}
		sumaActual = sumaActual + v[actual];
		if(debug){cout << "Suma Actual+: " << sumaActual << endl;}		

		if(sumaActual<0){			
			inicio = actual;
			sumaActual = 0;
			actual++;							
		}else{
			if(sumaActual>max){max = sumaActual;}
			if(debug){cout << "Max: " << max << endl;}
			actual++;
		}	
	}

	if(debug){cout << "Inicio: " << inicio << endl;}
	if(debug){cout << "Actual: " << actual << endl;}
	if(debug){cout << "sumaActual: " << sumaActual << endl;}


	return max;
}

void testManuales(){
	vector<vector<int> > bateriaTests;
	vector<int> resPosta;
	vector<int> res;

	vector<int> test1;
	vector<int> test2;
	vector<int> test3;
	vector<int> test4;
	vector<int> test5;
	vector<int> test6;
	
	test1.push_back(2);
	test1.push_back(-1);
	test1.push_back(2);
	resPosta.push_back(3);
		
	test2.push_back(-1);
	test2.push_back(-1);
	test2.push_back(-1);
	test2.push_back(-1);
	resPosta.push_back(0);
	
	test3.push_back(1);
	test3.push_back(2);
	test3.push_back(3);
	test3.push_back(4);
	test3.push_back(5);
	test3.push_back(-1);
	test3.push_back(-2);
	test3.push_back(-3);
	test3.push_back(-4);
	test3.push_back(-5);
	test3.push_back(1);
	test3.push_back(2);
	test3.push_back(3);
	test3.push_back(4);	
	resPosta.push_back(15);

	test4.push_back(1);
	test4.push_back(2);
	test4.push_back(3);
	test4.push_back(4);
	test4.push_back(5);
	test4.push_back(0);
	test4.push_back(-2);
	test4.push_back(-3);
	test4.push_back(0);
	test4.push_back(0);
	test4.push_back(1);
	test4.push_back(2);
	test4.push_back(3);
	test4.push_back(4);
	test4.push_back(0);
	test4.push_back(1);
	test4.push_back(6);
	resPosta.push_back(17);
	
	test5.push_back(1);
	test5.push_back(-1);
	test5.push_back(1);
	test5.push_back(-1);
	test5.push_back(1);
	test5.push_back(-1);
	test5.push_back(2);
	resPosta.push_back(2);

	test6.push_back(0);
	test6.push_back(0);
	test6.push_back(1);
	test6.push_back(-1);
	test6.push_back(1);
	test6.push_back(-1);
	test6.push_back(2);
	resPosta.push_back(2);

	bateriaTests.push_back(test1);
	bateriaTests.push_back(test2);
	bateriaTests.push_back(test3);
	bateriaTests.push_back(test4);
	bateriaTests.push_back(test5);
	bateriaTests.push_back(test6);
	

	for (int i = 0; i < bateriaTests.size(); ++i)	{
		res.push_back(sumaMax(bateriaTests[i]));
	}	

	for (int i = 0; i < res.size(); i++){
		cout << res[i] <<  " "  << resPosta[i]  <<endl;		
	}
}

vector<int> parser(char* file){
  ifstream in(file);
  vector<int> res;

  if (in.is_open()){
    int cantNum;  
    int numero;
  
    in >> cantNum;
    if(debug){cout << cantNum << endl;}
    
    for (int i = 0; i < cantNum; ++i){
      in >> numero;
      if(debug){cout << numero << endl;}
      res.push_back(numero);      
    }
  }
  return(res);
}
