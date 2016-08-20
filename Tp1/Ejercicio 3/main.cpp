#include "func.h"
using namespace std;

int main(int argc, char *argv[]){

	//testManuales();	
	vector<int> a = parser(argv[1]);
	for (int i = 0; i < a.size(); ++i)
	{
		cout<< a[i];
	}


	

	
	return 0;
}