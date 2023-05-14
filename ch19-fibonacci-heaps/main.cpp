#include <iostream>
#include "fibheap.h"
using namespace std;

int main() {
	char op;
	FibHeap H;
	pair<int,int> k;
	
	cout << "Choose an operation to perform (d/e/i/m/p/r/s/u): ";
	while (cin >> op) {

		if (op == 'd') {
			cout << "Element: ";
			cin >> k.first;
			try {
				H.remove(k.first);
			} catch (logic_error e) {
				cerr << e.what() << endl;
			}
		}
		else if (op == 'e') {
			try {
				k = H.extract_min();
				cout << "(" << k.first << "," << k.second << ")" << endl;
			} catch (underflow_error e) {
				cout << e.what() << endl;
			}
		}
		else if (op == 'i') {
			cout << "Element: ";
			cin >> k.first >> k.second;
			H.insert(k.first, k.second);
		}
		else if (op == 'm') {
			try {
				k = H.minimum();
				cout << "(" << k.first << "," << k.second << ")" << endl;
			} catch (underflow_error e) {
				cout << e.what() << endl;
			}
		}
		else if (op == 'p') {

		}
		else if (op == 'r')
			cout << H;
		else if (op == 's')
			cout << H.size() << endl;
		else if (op == 'u') {
			cout << "Element: ";
			cin >> k.first >> k.second;
			try {
				H.update(k.first, k.second);
			} catch (logic_error e) {
				cout << e.what() << endl;
			}
		}
		else
			cout << "Invalid response." << endl;
		
		cout << "Choose an operation to perform (d/e/i/m/p/r/s/u): ";
	}
	cout << endl;

	return 0;
}
