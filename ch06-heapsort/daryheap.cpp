#include <climits>
#include "daryheap.h"

ostream& operator<<(ostream& out, const MaxHeap& H) { 
	for (int i = 0; i < H.s; i++) 
		out << H.A[i] << " ";
	return out;
}

MaxHeap::MaxHeap(vector<int> B, int deg) {
	A = B;
	d = deg;
	s = B.size();
	build_max_heap();
}

void MaxHeap::heapify(int i) {
	int l = d*i + 1;
	int m = i;
	for (int j = l; j < l+d; j++) {
		if (j >= s) 
			break;
		if (A[j] > A[m])
			m = j;
	}
	if (m != i) {
		swap(A[i], A[m]);
		heapify(m);
	}
}

void MaxHeap::build_max_heap() {
	for (int i = (s-2)/d; i >= 0; i--)
		heapify(i);
}

int MaxHeap::size() {
	return s;
}

vector<int> MaxHeap::sort() {
	vector<int> B = A;
	int n = s;
	for (int i = n-1; i > 0; i--) {
		swap(A[0], A[i]);
		s--;
		heapify(0);
	}
	s = n;
	vector<int> C = A;
	A = B;
	return C;
}

int MaxHeap::extract_max() {
	if (s < 1)
		__throw_underflow_error("The heap is empty.");
	int max = A[0];
	A[0] = A[--s];
	A.pop_back();
	heapify(0);
	return max;
}

void MaxHeap::increase_key(int k, int i) {
	if (i < 0 || s <= i)
		__throw_out_of_range("Invalid index.");
	if (k < A[i])
		__throw_logic_error("New key is smaller than the current key.");
	A[i] = k;
	while (i > 0 && A[i] > A[(i-1)/d]) {
		swap(A[i], A[(i-1)/d]);
		i = (i-1)/d;
	}
}

void MaxHeap::insert(int k) {
	A.push_back(INT_MIN);
	increase_key(k, s++);
}
