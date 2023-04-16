#include <iostream>
#include <climits>
#include <queue>
using namespace std;

struct Node {
	int v;
	Node *l = nullptr;
	Node *r = nullptr;
};

int main() {
	int n, smin = INT_MAX;

	cout << "Number of Elements: ";
	cin >> n;
	if (n < 2) return 0;

	queue<Node*> q;
	Node *root;
	cout << "Elements: ";
	for (int i = 0; i < n; i++) {
		root = new Node();
		cin >> root->v;
		q.push(root);
	}

	while (q.size() > 1) {
		Node *m = q.front();
		q.pop();
		Node *n = q.front();
		q.pop();
		root = new Node;
		if (m->v < n->v) {
			root->v = m->v;
			root->l = m;
			root->r = n;
		} else {
			root->v = n->v;
			root->l = n;
			root->r = m;
		}
		q.push(root);
	}
	root = q.front();

	while (root->l != nullptr) {
		smin = min(smin, root->r->v);
		root = root->l;
	}

	cout << smin << endl;
	return 0;
}
