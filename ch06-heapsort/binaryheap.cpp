#include <iostream>
#include <climits>
#include <vector>
using namespace std;

class BinaryMaxHeap {
	friend ostream &operator<<(ostream &os, const BinaryMaxHeap &H);
	public:
		BinaryMaxHeap(vector<int> B);
		int size();
		vector<int> sort();
		int extract_max();
		void increase_key(int i, int k);
		void insert(int k);
	private:
		vector<int> A;
		void heapify(int i);
		void build_max_heap();
};

ostream &operator<<(ostream &os, const BinaryMaxHeap &H) { 
	for (int i=1; i<=H.A[0]; i++) 
		os << H.A[i] << " ";
	return os;
}

BinaryMaxHeap::BinaryMaxHeap(vector<int> B) {
	if (B.size()) {
		A.push_back(B.size());
		A.reserve(B.size() + 1);
		for (int x: B) A.push_back(x);
		build_max_heap();
	}
	else A.push_back(0);
}

void BinaryMaxHeap::heapify(int i) {
	int l = i<<1;
	int r = (i<<1) + 1;
	int m = i;
	if (l <= A[0] && A[l] > A[i])
		m = l;
	if (r <= A[0] && A[r] > A[m])
		m = r;
	if (m != i) {
		swap(A[i], A[m]);
		heapify(m);
	}
}

void BinaryMaxHeap::build_max_heap() {
	for (int i=A[0]>>1; i>0; i--)
		heapify(i);
}

int BinaryMaxHeap::size() {
	return A[0];
}

vector<int> BinaryMaxHeap::sort() {
	vector<int> B = A;
	int n = A[0];
	for (int i=n; i>1; i--) {
		swap(A[1], A[i]);
		A[0]--;
		heapify(1);
	}
	vector<int> C = A;
	A = B;
	C.erase(C.begin());
	return C;
}

int BinaryMaxHeap::extract_max() {
	if (A[0] < 1)
		__throw_underflow_error("The heap is empty.");
	int max = A[1];
	A[1] = A[A[0]];
	A[0]--;
	heapify(1);
	return max;
}

void BinaryMaxHeap::increase_key(int i, int k) {
	if (i > A[0])
		__throw_out_of_range("Index exceeded the size of heap.");
	if (i < 0)
		__throw_out_of_range("Invalid input.");
	if (k < A[i])
		__throw_logic_error("New key is smaller than the current key.");
	A[i] = k;
	while (i>1 && A[i] > A[i>>1]) {
		swap(A[i], A[i>>1]);
		i = i>>1;
	}
}

void BinaryMaxHeap::insert(int k) {
	A[0]++;
	A.push_back(INT_MIN);
	increase_key(A[0], k);
}

int main() {
	int n;
	cout << "Number of Elements: ";
	cin >> n;
	vector<int> A(n);
	cout << "Elements: ";
	for (int i=0; i<n; i++) 
		cin >> A[i];
	BinaryMaxHeap H(A);

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
