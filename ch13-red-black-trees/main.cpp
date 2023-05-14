#include <iostream>
#include "rbtree.h"
using namespace std;

int main() {
	RedBlackTree<int> T;
	char op;
	int num;

	cout << "Choose an operation (d/i/I/p): ";
	while (cin >> op) {

		if (op == 'd') {
			cout << "Enter the key: ";
			cin >> num;
			try {
				T.delete_key(num);
			} catch (logic_error e) {
				cout << e.what() << endl;
			}
		}
		else if (op == 'i')
			T.inorder_walk();
		else if (op == 'I') {
			cout << "Enter the key: ";
			cin >> num;
			T.insert_key(num);
		} 
		else if (op == 'p')
			T.postorder_walk();
		else 
			cout << "Invalid response." << endl;

		cout << "Choose an operation (d/i/I/p): ";
	}
	cout << endl;

	return 0;
}
