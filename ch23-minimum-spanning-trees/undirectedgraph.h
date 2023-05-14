#pragma once
#include <list>
#include <vector>
#include <iostream>
using namespace std;

class UndirectedGraph {
	friend istream& operator>>(istream& os, UndirectedGraph& G);
	friend ostream& operator<<(ostream& os, const UndirectedGraph& G);
	public:
		UndirectedGraph(int n);
		void kruskal();
		void prim(int r);
	private:
		vector<list<pair<int,int>>> A;
};
