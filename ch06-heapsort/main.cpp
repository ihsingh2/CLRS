#include <iostream>
#include <vector>
#include "daryheap.h"
#include "youngtableau.h"
using namespace std;

int main() {
	int n;
	cout << "Enter 0 for d-ary (max)heap, 1 for young tableau: ";
	cin >> n;

	if (n) {
		int r, c;
		cout << "Number of Rows: ";
		cin >> r;
		cout << "Number of Columns: ";
		cin >> c;
		YoungTableau Y(r,c);

		char op;
		pair<int,int> d;

		cout << "Choose an operation to perform (e/f/i/p/s): ";
		while (cin >> op) {

			if (op == 'e') {
				try {
					n = Y.extract_min();
					cout << "Extracted " << n << "." << endl;
				} catch (underflow_error e) {
					cerr << e.what() << endl;
				}
			}
			else if (op == 'f') {
				cout << "Element: ";
				cin >> n;
				try {
					d = Y.find(n);
					cout << "Found at (" << d.first << ", " << d.second << ")" << endl;
				} catch (logic_error e) {
					cerr << e.what() << endl;
				}
			}
			else if (op == 'i') {
				cout << "Element: ";
				cin >> n;
				try {
					Y.insert(n);
				} catch (overflow_error e) {
					cerr << e.what() << endl;
				}
			}
			else if (op == 'p')
				cout << Y;
			else if (op == 's') {
				vector<int> A = Y.sort();
				for (int x: A)
					cout << x << " ";
				if (A.size())
					cout << endl;
			} 
			else 
				cout << "Invalid response." << endl;
			
			cout << "Choose an operation to perform (e/f/i/p/s): ";
		}
	}
	
	else {
		int d;
		cout << "Number of Elements: ";
		cin >> n;
		vector<int> A(n);
		if (n > 0)
			cout << "Elements: ";
		for (int i = 0; i < n; i++)
			cin >> A[i];
		cout << "Degree: ";
		cin >> d;
		MaxHeap H(A, d);

		char op;
		int i, k;

		cout << "Choose an operation to perform (i/m/p/s/u): ";
		while (cin >> op) {

			if (op == 'i') {
				cout << "Element: ";
				cin >> k;
				H.insert(k);
			}
			else if (op == 'm') {
				try {
					k = H.extract_max();
					cout << "Extracted " << k << "." << endl;
				} catch (underflow_error e) {
					cerr << e.what() << endl;
				}
			}
			else if (op == 'p') {
				cout << H;
				if (H.size() > 0) 
					cout << endl;
			}
			else if (op == 's') {
				A = H.sort();
				for (int x: A) 
					cout << x << " ";
				if (A.size()) 
					cout << endl;
			}
			else if (op == 'u') {
				cout << "Key: ";
				cin >> k;
				cout << "Index: ";
				cin >> i;
				try {
					H.increase_key(k, i);
				} catch (logic_error e) {
					cerr << e.what() << endl;
				}
			}
			else
				cout << "Invalid response." << endl;

			cout << "Choose an operation to perform (i/m/p/s/u): ";
		}
	}

	cout << endl;

	return 0;
}
