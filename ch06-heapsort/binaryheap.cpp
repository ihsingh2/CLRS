#include "binaryheap.h"

MinHeap::MinHeap(vector<pair<int,int>> D) {
	A = D;
	for (int i = 0; i < D.size(); i++)
		M[D[i].second] = i;
	build_min_heap();
}

void MinHeap::heapify(int i) {
	int l = (i << 1) + 1;
	int r = (i << 1) + 2;
	int m = i;
	if (l < A.size() && A[m].first > A[l].first)
		m = l;
	if (r < A.size() && A[m].first > A[r].first)
		m = r;
	if (m != i) {
		swap(M[A[i].second], M[A[m].second]);
		swap(A[i], A[m]);
		heapify(m);
	}
}

void MinHeap::build_min_heap() {
	for (int i = (A.size() - 2) >> 1; i >= 0; i--)
		heapify(i);
}

int MinHeap::size() {
	return A.size();
}

bool MinHeap::empty() {
	return A.empty();
}

int MinHeap::peek(int u) {
	if (M.find(u) == M.end())
		__throw_invalid_argument("Value not in heap.");
	return A[M.at(u)].first;
}

pair<int,int> MinHeap::pop() {
	if (A.size() < 1)
		__throw_underflow_error("The heap is empty.");
	pair<int,int> max = A[0];
	M.erase(A[0].second);
	M[A[A.size() - 1].second] = 0;
	A[0] = A[A.size() - 1];
	A.pop_back();
	heapify(0);
	return max;
}

void MinHeap::decrease_key(int i, int k) {
	if (k >= A[i].first)
		__throw_logic_error("New key should be smaller than the current key.");
	A[i].first = k;
	while (i > 0 && A[i].first < A[(i - 1) >> 1].first) {
		swap(M[A[i].second], M[A[(i - 1) >> 1].second]);
		swap(A[i], A[(i - 1) >> 1]);
		i = (i - 1) >> 1;
	}
}

void MinHeap::update(int u, int k) {
	if (M.find(u) == M.end())
		__throw_invalid_argument("Value not in heap.");
	decrease_key(M[u], k);
}
