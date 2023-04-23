#include <iostream>
#include <climits>
#include <vector>
using namespace std;

class MaxHeap {
	friend ostream& operator<<(ostream& out, const MaxHeap& H);
	public:
		MaxHeap(vector<int> B, int deg);
		int size();
		vector<int> sort();
		int extract_max();
		void increase_key(int i, int k);
		void insert(int k);
	private:
		vector<int> A;
		int d;
		int s;
		void heapify(int i);
		void build_max_heap();
};

ostream& operator<<(ostream& out, const MaxHeap& H) { 
	for (int i = 0; i < H.s; i++) 
		out << H.A[i] << " ";
	return out;
}

MaxHeap::MaxHeap(vector<int> B, int deg) {
	d = deg;
	s = B.size();
	if (B.size()) {
		A.reserve(B.size());
		for (int x: B)
			A.push_back(x);
		build_max_heap();
	}
}

void MaxHeap::heapify(int i) {
	int l = d*i + 1;
	int m = i;
	for (int j=l; j<l+d; j++) {
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
	int max = A[1];
	A[1] = A[s-1];
	s--;
	heapify(1);
	return max;
}

void MaxHeap::increase_key(int i, int k) {
	if (i >= s)
		__throw_out_of_range("Index exceeded the size of heap.");
	if (i < 0)
		__throw_out_of_range("Invalid input.");
	if (k < A[i])
		__throw_logic_error("New key is smaller than the current key.");
	A[i] = k;
	while (i>0 && A[i] > A[(i-1)/d]) {
		swap(A[i], A[(i-1)/d]);
		i = (i-1)/d;
	}
}

void MaxHeap::insert(int k) {
	A.push_back(INT_MIN);
	increase_key(s, k);
	s++;
}

int main() {
	int n, d;
	cout << "Number of Elements: ";
	cin >> n;
	vector<int> A(n);
	cout << "Elements: ";
	for (int i = 0; i < n; i++)
		cin >> A[i];
	if (n < 1) 
		cout << endl;
	cout << "Degree: ";
	cin >> d;
	MaxHeap H(A, d);

	char op;
	int i, k;

	cout << "Use 'i' for increase and 'I' for insert." << endl;
	cout << "Choose an operation to perform (i/I/M/P/S): ";
	while (cin >> op) {
		if (op == 'i') {
			cout << "Enter the index: ";
			cin >> i;
			cout << "Enter the key: ";
			cin >> k;
			try {
				H.increase_key(i, k);
			} catch (logic_error e) {
				cerr << e.what() << endl;
			}
		} else if (op == 'I') {
			cout << "Enter the element: ";
			cin >> k;
			H.insert(k);
		} else if (op == 'M') {
			try {
				k = H.extract_max();
				cout << "Extracted " << k << "." << endl;
			} catch (underflow_error e) {
				cerr << e.what() << endl;
			}
		} else if (op == 'P') {
			cout << H;
			if (H.size() > 0) 
				cout << endl;
		} else if (op == 'S') {
			A = H.sort();
			for (int x: A) cout << x << " ";
			if (A.size()) cout << endl;
		} else cout << "Invalid response." << endl;
		cout << "Choose an operation to perform (i/I/M/P/S): ";
	}
	cout << endl;

	return 0;
}
