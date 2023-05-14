#pragma once
#include <vector>
#include <iostream>
using namespace std;

class MaxHeap {
	friend ostream& operator<<(ostream& out, const MaxHeap& H);
	public:
		MaxHeap(vector<int> B, int deg);
		int size();
		vector<int> sort();
		int extract_max();
		void increase_key(int k, int i);
		void insert(int k);
	private:
		vector<int> A;
		int d;
		int s;
		void heapify(int i);
		void build_max_heap();
};
