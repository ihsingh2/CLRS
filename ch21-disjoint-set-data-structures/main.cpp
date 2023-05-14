#include <iostream>
#include "disjointset.h"
using namespace std;

int main() {
	int m, n;
	char op;
	cout << "Number of Elements: ";
	cin >> n;
	DisjointSet S(n);

	cout << "Choose an operation (f/p/u): ";
	while (cin >> op) {

		if (op == 'f') {
			cout << "Element: ";
			cin >> n;
			try {
				cout << S.find_set(n) << endl;
			} catch (out_of_range e) {
				cout << e.what() << endl;
			}
		}
		else if (op == 'p')
			cout << S;
		else if (op == 'u') {
			cout << "Elements: ";
			cin >> m >> n;
			try {
				S.union_set(m, n);
			} catch (out_of_range e) {
				cout << e.what() << endl;
			}
		} 
		else 
			cout << "Invalid response." << endl;

		cout << "Choose an operation (f/p/u): ";
	}
	cout << endl;

	return 0;
}
