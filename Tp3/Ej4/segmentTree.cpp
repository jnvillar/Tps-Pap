#include <iostream>
#include <vector>
#include <assert.h> 
#include <queue>
#include <stack>
#include <utility>
#include "math.h"

using namespace std;


class SegmentTree{
	public:
		SegmentTree(vector<int> val){

			if (pow(2,(int )log2(val.size())) != val.size()){
				val.resize(pow(2,(int )log2(val.size())+1),0);
			}
			n = val.size();
			arbol.resize(2*n-1); 
			for(int i = 0; i<n; i++){
				arbol[n+i-1].first = val[i];
				arbol[n+i-1].second = 0;
			}
			for(int i = n-2; i>=0; i--){
				arbol[i].first = max(arbol[2*i+1].first, arbol[2*i+2].first);
				int val = max(arbol[2*i+1].second, arbol[2*i+2].second);
				arbol[i].second = max(val, min(arbol[2*i+1].first, arbol[2*i+2].first));
			}

			/*
			for(int i = 0; i< arbol.size(); i++){
				cout << arbol[i].first << "-" << arbol[i].second << "  ";
			}
			cout << endl;
			*/
		}

		int query(int i, int j){
			pair<int,int> res = funcRecursiva(0,0,n,i,j);
			return res.first + res.second;
		}

		pair<int,int> funcRecursiva(int k, int l, int r, int i, int j){
			pair<int,int> res;
			if (i <= l && l < r && r <= j){
				res = arbol[k];
			} else if(r <= i || l >= j){
				pair<int,int> infinito(-10,-10);
				res = infinito;
			} else {
				pair<int,int> resHijoIzq = funcRecursiva(2*k+1,l,(l+r)/2,i,j);
				pair<int,int> resHijoDer = funcRecursiva(2*k+2,(l+r)/2,r,i,j);
				res.first = max(resHijoIzq.first, resHijoDer.first);
				int val = max(resHijoIzq.second, resHijoDer.second);
				res.second = max(val, min(resHijoIzq.first, resHijoDer.first));
			}

			return res;
		}

	private:
		vector< pair<int,int> > arbol;
		int n;

};



/*

class SegmentTree{
	public:
		SegmentTree(vector<int> val){

			if (pow(2,log2(val.size())) != val.size()){
				val.resize(pow(2,log2(val.size())+1),0);
			}
			n = val.size();
			arbol.resize(2*n-1); 
			for(int i = 1; i<=n; i++){
				arbol[n+i-1].first = val[i-1];
				arbol[n+i-1].second = 0;
			}
			for(int i = n-1; i>=1; i--){
				arbol[i-1].first = max(arbol[2*i].first, arbol[2*i+1].first);
				int val = max(arbol[2*i].second, arbol[2*i+1].second);
				arbol[i-1].second = max(val, min(arbol[2*i].first, arbol[2*i+1].first));
			}


			for(int i = 0; i< arbol.size(); i++){
				cout << arbol[i].first << "-" << arbol[i].second << "  ";
			}
			cout << endl;
		}

		int query(int i, int j){
			pair<int,int> res = funcRecursiva(1,0,n,i,j);
			return res.first + res.second;
		}

		pair<int,int> funcRecursiva(int k, int l, int r, int i, int j){
			pair<int,int> res;
			if (i <= l && l < r && r <= j){
				res = arbol[k-1];
			} else if(r <= i || l >= j){
				pair<int,int> infinito(-10,-10);
				res = infinito;
			} else {
				pair<int,int> resHijoIzq = funcRecursiva(2*k,l,(l+r)/2,i,j);
				pair<int,int> resHijoDer = funcRecursiva(2*k+1,(l+r)/2,r,i,j);
				res.first = max(resHijoIzq.first, resHijoDer.first);
				int val = max(resHijoIzq.second, resHijoDer.second);
				res.second = max(val, min(resHijoIzq.first, resHijoDer.first));
			}

			return res;
		}

	private:
		vector< pair<int,int> > arbol;
		int n;

};

*/