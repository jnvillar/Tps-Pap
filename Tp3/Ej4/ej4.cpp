#include <iostream>
#include <string>
#include <vector>
#include "segmentTree.cpp"


using namespace std;



int main(){
	/*
	vector<int> vec;
	vec.push_back(6);
	vec.push_back(2);
	vec.push_back(4);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(8);
	vec.push_back(2);
	SegmentTree st(vec);
	
	cout << st.query(2,5) << endl;
	cout << st.query(3,8) << endl;
	*/
	int d,r;
	cin >> d;
	cin >> r;
	vector<int> vec;
	for(int i = 0; i<d; i++){
		int val;
		cin >> val;
		vec.push_back(val);
	}

	SegmentTree st(vec);
	for(int i = 0; i<r; i++){
		int queryDesde, queryHasta;
		cin >> queryDesde;
		cin >> queryHasta;
		cout << st.query(queryDesde,queryHasta) << endl;
	}
	
	return 0;
}

