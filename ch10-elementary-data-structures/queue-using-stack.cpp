#include <iostream>
#include <stack>
using namespace std;

class Queue {
	public:
		void Enqueue(int x);
		int Dequeue();
	private:
		stack<int> A, B;
};

void Queue::Enqueue(int x) {
	A.push(x);
}

int Queue::Dequeue() {
	if (A.empty() && B.empty())
		__throw_underflow_error("The queue is empty.");
	if (B.empty()) {
		while (!A.empty()) {
			B.push(A.top());
			A.pop();
		}
	}
	int x = B.top();
	B.pop();
	return x;
}

int main() {
	Queue q;
	char op;
	int num;

	cout << "Choose an operation to perform (E/D): ";
	while (cin >> op) {
		if (op == 'E') {
			cout << "Enter the element: ";
			cin >> num;
			q.Enqueue(num);
		} else if (op == 'D') {
			try {
				num = q.Dequeue();
				cout << "Dequeued " << num << "." << endl;
			} catch (underflow_error e) {
				cerr << e.what() << endl;
			}
		} else cout << "Invalid response." << endl;
		cout << "Choose an operation to perform (E/D): ";
	}
	cout << endl;

	return 0;
}