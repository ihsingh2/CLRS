#pragma once
#include <vector>
#include <unordered_map>
using namespace std;

class MinHeap {
	public:
		MinHeap(vector<pair<int,int>> D);
		int size();
		bool empty();
		int peek(int u);
		pair<int,int> pop();
		void update(int v, int k);
	private:
		vector<pair<int,int>> A;
		unordered_map<int,int> M;
		void heapify(int i);
		void build_min_heap();
		void decrease_key(int i, int k);
};
