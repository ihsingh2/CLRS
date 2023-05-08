#include <iostream>
#include <climits>
#include <cmath>
#include <vector>
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
		void insert(int k, int v);
		pair<int,int> minimum();
		pair<int,int> extract_min();
		void update(int v, int k);
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

ostream& operator<<(ostream& out, const FibHeap& H) {
	FibHeapNode *x = H.min;
	if (x != nullptr) {
		do {
			out << "(" << x->key << "," << x->value << ")" << endl;
			x = x->right;
		} while (x != H.min);
	}
	return out;
}

FibHeap::FibHeap() {
	n = 0;
	log2_gr = log2(1.62);
	min = nullptr;
}

int FibHeap::size() {
	return n;
}

void FibHeap::add_to_root_list(FibHeapNode *x) {
	if (min == nullptr) {
		min = x;
		x->left = x;
		x->right = x;
	}
	else {
		min->left->right = x;
		x->left = min->left;
		min->left = x;
		x->right = min;
		x->parent = nullptr;
		if (x->key < min->key)
			min = x;
	}
}

void FibHeap::insert(int k, int v) {
	FibHeapNode *x = new FibHeapNode(k, v);
	M[v] = x;
	add_to_root_list(x);
	n++;
}

pair<int,int> FibHeap::minimum() {
	if (min == nullptr)
		__throw_underflow_error("Heap is empty.");
	return make_pair(min->key, min->value);
}

pair<int,int> FibHeap::extract_min() {
	if (min == nullptr)
		__throw_underflow_error("Heap is empty.");
	
	FibHeapNode *z = min;
	FibHeapNode *x = z->child;
	if (x != nullptr) {
		while (x->parent != nullptr) {
			FibHeapNode *y = x->right;
			add_to_root_list(x);
			x = y;
		}
	}

	if (z == z->right)
		min = nullptr;
	else {
		z->right->left = z->left;
		z->left->right = z->right;
		min = z->right;
		consolidate();
	}

	pair<int,int> res(z->key, z->value);
	M.erase(z->value);
	delete z;
	n--;
	return res;
}

void FibHeap::consolidate() {
	vector<FibHeapNode*> A((log2(n) / log2_gr) + 1, nullptr);

	FibHeapNode *x = min;
	bool minreached = false;
	do {
		x = x->right;
		int d = x->degree;
		if (x == min)
			minreached = true;
		while (A[d] != nullptr && A[d] != x) {
			FibHeapNode *y = A[d];
			if (x->key > y->key)
				swap(x,y);
			link(y,x);
			A[d] = nullptr;
			d++;
		}
		A[d] = x;
	} while (!minreached);
	
	min = nullptr;
	for (int i = 0; i < A.size(); i++)
		if (A[i] != nullptr)
			add_to_root_list(A[i]);
}

void FibHeap::link(FibHeapNode *y, FibHeapNode *x) {
	y->right->left = y->left;
	y->left->right = y->right;
	y->parent = x;
	y->mark = 0;
	x->degree++;

	if (x->child == nullptr) {
		x->child = y;
		y->left = y;
		y->right = y;
	}
	else {
		x->child->left->right = y;
		y->left = x->child->left;
		x->child->left = y;
		y->right = x->child;
	}
}

void FibHeap::update(int v, int k) {
	if (M.find(v) == M.end())
		__throw_invalid_argument("Value not in heap.");
	FibHeapNode *x = M.at(v);
	if (k > x->key)
		__throw_logic_error("New key should be smaller than the current key.");

	x->key = k;
	FibHeapNode *y = x->parent;
	if (y != nullptr && x->key < y->key) {
		cut(x, y);
		cascading_cut(y);
	}
}

void FibHeap::cut(FibHeapNode *x, FibHeapNode *y) {
	if (y->degree == 1)
		y->child = nullptr;
	else {
		x->right->left = x->left;
		x->left->right = x->right;
		if (y->child == x)
			x->right;
	}
	y->degree--;
	add_to_root_list(x);
	x->mark = 0;
}

void FibHeap::cascading_cut(FibHeapNode *y) {
	if (y->parent != nullptr) {
		if (y->mark == 0)
			y->mark = 1;
		else {
			cut(y, y->parent);
			cascading_cut(y->parent);
		}
	}
}

void FibHeap::remove(int v) {
	update(v, INT_MIN);
	extract_min();
}

int main() {
	char op;
	FibHeap H;
	pair<int,int> k;
	
	cout << "Choose an operation to perform (e/i/m/p/r/s/u): ";
	while (cin >> op) {
		if (op == 'e') {
			try {
				k = H.extract_min();
				cout << "(" << k.first << "," << k.second << ")" << endl;
			} catch (underflow_error e) {
				cout << e.what() << endl;
			}
		} else if (op == 'i') {
			cout << "Element: ";
			cin >> k.first;
			H.insert(k.first, k.first);
		} else if (op == 'm') {
			try {
				k = H.minimum();
				cout << "(" << k.first << "," << k.second << ")" << endl;
			} catch (underflow_error e) {
				cout << e.what() << endl;
			}
		} else if (op == 'p') {
			cout << H;
		} else if (op == 'r') {
			cout << "Element: ";
			cin >> k.first;
			try {
				H.remove(k.first);
			} catch (logic_error e) {
				cerr << e.what() << endl;
			}
		} else if (op == 's') {
			k.first = H.size();
			cout << k.first << endl;
		} else if (op == 'u') {
			cout << "Element: ";
			cin >> k.first >> k.second;
			try {
				H.update(k.second, k.first);
			} catch (logic_error e) {
				cout << e.what() << endl;
			}
		} else cout << "Invalid response." << endl;
		cout << "Choose an operation to perform (e/i/m/p/r/s/u): ";
	}
	cout << endl;

	return 0;
}
