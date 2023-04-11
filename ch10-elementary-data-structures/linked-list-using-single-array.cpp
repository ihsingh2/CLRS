#include <iostream>
using namespace std;
#define SIZE 1024 // inclusive of sentinel, i.e. NIL

class List {
	public:
		List();
		void Print();
		void Insert(int x);
		void Delete(int x);
		void Compactify();
	private:
		int A[SIZE*3]; 	// single array representation: prev, key, next - in that order.
		int NIL;
		int free;
		int Search(int x);
		void SwapNode(int x, int y);
};

List::List() {
	// sentinel: self-referencing first element
	NIL = 0;
	A[2] = 0;
	// free list: second, third ... to the first element
	free = 3;
	for (int i = 3; i < SIZE*3; i += 3) A[i+2] = i+3;
	A[SIZE*3 - 1] = NIL;
}

void List::Print() {
	if (A[NIL+2] == NIL) return;
	int node = A[NIL+2];
	cout << A[node+1];
	while (A[node+2] != NIL) {
		node = A[node+2];
		cout << "->" << A[node+1];
	}
	cout << endl;
}

void List::Insert(int x) {
	if (free == NIL) {
		cout << "List size exhausted." << endl;
		return;
	}

	int node = free;
	free = A[node+2];

	A[node] = NIL;
	A[node+1] = x;
	A[node+2] = A[NIL+2];
	
	A[A[NIL+2]] = node;
	A[NIL+2] = node;
}

void List::Delete(int x) {
	int node = Search(x);
	if (node == NIL) return;
	else {
		A[A[node]+2] = A[node+2];
		A[A[node+2]] = A[node];
		A[node+2] = free;
		free = node;
	}
}

void List::Compactify() {
	int i = 3, l = A[NIL+2];
	while (l != NIL) {
		SwapNode(l, i);
		if (free == i)
			free = l;
		l = A[i+2];
		i += 3;
	}
}

int List::Search(int x) {
	int node = A[NIL+2];
	while (node != NIL && A[node+1] != x)
		node = A[node+2];
	return node;
}

void List::SwapNode(int x, int y) {
	swap(A[x], A[y]);
	swap(A[x+1], A[y+1]);
	swap(A[x+2], A[y+2]);

	// update other nodes linked to x and y
	if (A[A[x]+2] == y) A[A[x]+2] = x;
	if (A[A[x+2]] == y) A[A[x+2]] = x;
	if (A[A[y]+2] == x) A[A[y]+2] = y;
	if (A[A[y+2]] == x) A[A[y+2]] = y;

	// update x and y's links to each other
	if (A[x] == x) A[x] = y;
	if (A[x+2] == x) A[x+2] = y;
	if (A[y] == y) A[y] = x;
	if (A[y+2] == y) A[y+2] = x;	
}

int main() {
	List lst;
	char op;
	int num;

	cout << "Choose an operation (I/D/C/P): ";
	while (cin >> op) {
		if (op == 'I') {
			cout << "Enter the key: ";
			cin >> num;
			lst.Insert(num);
		} else if (op == 'D') {
			cout << "Enter the key: ";
			cin >> num;
			lst.Delete(num);
		} else if (op == 'C') {
			lst.Compactify();
		} else if (op == 'P') {
			lst.Print();
		} else cout << "Invalid response." << endl;
		cout << "Choose an operation (I/D/C/P): ";
	}
	cout << endl;

	return 0;
}
