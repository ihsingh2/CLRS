#include <iostream>
using namespace std;
#define SIZE 1024 // inclusive of sentinel, i.e. NIL

class List {
		// single array representation: prev, key, next - in that order.
		int A[SIZE*3]; 
		int NIL;
		int free;

	public:

		List() {
			// sentinel: self-referencing first element
			NIL = 0;
			A[2] = 0;

			// free list: second, third ... to the first element
			free = 3;
			for (int i = 3; i < SIZE*3; i += 3) A[i+2] = i+3;
			A[SIZE*3 - 1] = NIL;
		}

		void Print() {
			if (A[NIL+2] == NIL) return;

			int node = A[NIL+2];
			cout << A[node+1];
			while (A[node+2] != NIL) {
				node = A[node+2];
				cout << "->" << A[node+1];
			}
			cout << endl;
		} 

		/* void PrintEverything(int x) {
			cout << "F: " << free << "; A:";
			for (int i=0; i<x*3; i++) {
				if (i%3 == 0) cout << "\t";
				cout << A[i] << " ";
			}
			cout << endl;
		} */

		void Insert(int x) {
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

		int Search(int x) {
			int node = A[NIL+2];
			while (node != NIL && A[node+1] != x)
				node = A[node+2];
			return node;
		}

		void Delete(int x) {
			int node = Search(x);
			if (node == NIL) return;
			else {
				A[A[node]+2] = A[node+2];
				A[A[node+2]] = A[node];
				A[node+2] = free;
				free = node;
			}
		}

		void Compactify() {
			int i = 3, l = A[NIL+2];
			while (l != NIL) {
				SwapNode(l, i);
				if (free == i)
					free = l;
				l = A[i+2];
				i += 3;
			}
		}

	private:

		void SwapNode(int x, int y) {

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
};

int main() {
	List lst;
	char op;
	int num, res;

	while (true) {
		cout << "Choose an operation (I/S/D/C/P): ";
		cin >> op;

		if (op == 'I') {
			cout << "Enter the key: ";
			cin >> num;
			lst.Insert(num);
		} else if (op == 'S') {
			cout << "Enter the key: ";
			cin >> num;
			res = lst.Search(num);
			if (res>0) cout << "Found at: " << res << endl;
			else cout << "Not found." << endl;
		} else if (op == 'D') {
			cout << "Enter the key: ";
			cin >> num;
			lst.Delete(num);
		} else if (op == 'C') {
			lst.Compactify();
		} else if (op == 'P') {
			lst.Print();
		} /* else if (op == 'E') {
			lst.PrintEverything(10);
		} */ else cout << "Invalid response." << endl;
	}

	return 0;
}
