#pragma once
#include <list>
#include <vector>
#include <iostream>
using namespace std;

class DisjointSet {
	friend ostream& operator<<(ostream& out, const DisjointSet& S);
	public:
		DisjointSet(int n);
		int find_set(int x);
		void union_set(int x, int y);
	private:
		int size;
		vector<int> rank;
		vector<int> parent;
		vector<list<int>> set;
		void link_set(int x, int y);
};
