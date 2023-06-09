#include <iostream>
#include <queue>
using namespace std;

class Stack {
	public:
		void Push(int x);
		int Pop();
		int Top();
	private:
		queue<int> A, B;
};

void Stack::Push(int x) {
	A.push(x);
}

int Stack::Pop() {
	if (A.empty())
		__throw_underflow_error("The stack is empty.");
	while (A.size() != 1) {
		B.push(A.front());
		A.pop();
	}
	int x = A.front();
	A.pop();
	queue<int> C;
	C = B;
	B = A;
	A = C;
	return x;
}

int Stack::Top() {
	if (A.empty())
		__throw_underflow_error("The stack is empty.");
	while (A.size() != 1) {
		B.push(A.front());
		A.pop();
	}
	int x = A.front();
	A.pop();
	B.push(x);
	queue<int> C;
	C = B;
	B = A;
	A = C;
	return x;
}

int main() {
	Stack s;
	char op;
	int num;

	cout << "Use 'P' for push and 'p' for pop." << endl;
	cout << "Choose an operation to perform (P/p/t): ";
	while (cin >> op) {
		if (op == 'P') {
			cout << "Enter the element: ";
			cin >> num;
			s.Push(num);
		} else if (op == 'p') {
			try {
				num = s.Pop();
				cout << "Popped " << num << "." << endl;
			} catch (underflow_error e) {
				cerr << e.what() << endl;
			}
		} else if (op == 't') {
			try {
				num = s.Top();
				cout << "Top element is " << num << "." << endl;
			} catch (underflow_error e) {
				cerr << e.what() << endl;
			}
		} else cout << "Invalid response." << endl;
		cout << "Choose an operation to perform (P/p/t): ";
	}
	cout << endl;

	return 0;
}