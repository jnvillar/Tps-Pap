#include "func.h"
using namespace std;

int main(){

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
		cout << res[i] <<  " "  <<resPosta[i]  <<endl;		
	}

	
	return 0;
}