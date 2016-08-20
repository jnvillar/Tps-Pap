#include "func.h"
using namespace std;

int main(int argc, char *argv[]){

	//entrar por consola
	vector<int> v;
	int cant;
	cin >> cant;
	for (int i = 0; i<cant; i++){
		int val;
		cin >> val;
		v.push_back(val);
	}
	int res = sumaMax(v);

	//testManuales();	
	vector<int> a = parser(argv[1]);
	for (int i = 0; i < a.size(); ++i)
	{
		cout<< a[i];
	}


	

	
	return 0;
}