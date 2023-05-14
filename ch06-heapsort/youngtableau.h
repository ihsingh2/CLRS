#pragma once
#include <vector>
#include <iostream>
using namespace std;

class YoungTableau {
	friend ostream& operator<<(ostream& out, const YoungTableau& Y);
	public:
		YoungTableau(int r, int c);
		int extract_min();
		void insert(int k);
		pair<int,int> find(int k);
		vector<int> sort();
	private:
		vector<vector<int>> A;
		int m;
		int n;
};
