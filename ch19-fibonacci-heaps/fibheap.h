#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;

class FibHeapNode {
	public:
		FibHeapNode(int k, int v) {
			key = k;
			value = v;
			degree = 0;
			mark = 0;
			parent = nullptr;
			child = nullptr;
			left = this;
			right = this;
		}
		int key;
		int value;
		int degree;
		int mark;
		FibHeapNode *parent;
		FibHeapNode *child;
		FibHeapNode *left;
		FibHeapNode *right;
};

class FibHeap {
	friend ostream& operator<<(ostream& out, const FibHeap& H);
	public:
		FibHeap();
		int size();
		int peek(int v);
		void insert(int k, int v);
		pair<int,int> minimum();
		pair<int,int> extract_min();
		void update(int k, int v);
		void remove(int v);
	private:
		int n;
		double log2_gr;
		FibHeapNode *min;
		unordered_map<int,FibHeapNode*> M;
		void add_to_root_list(FibHeapNode *x);
		void consolidate();
		void link(FibHeapNode *y, FibHeapNode *x);
		void cut(FibHeapNode *x, FibHeapNode *y);
		void cascading_cut(FibHeapNode *y);
};
