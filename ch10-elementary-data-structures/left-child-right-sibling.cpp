#include <iostream>
using namespace std;

struct Node {
	int key;
	bool hasSibling;
	struct Node *child = nullptr;
	struct Node *sibling = nullptr; // points to the parent when hasSibling = 0
};

struct Node* createNode(struct Node *root, bool hasSibling) {
	struct Node *node = new Node;
	if (hasSibling) node->hasSibling = 1;
	else {
		node->hasSibling = 0;
		node->sibling = root;
	}
	int i;
	cout << "Key: ";
	cin >> node->key;
	cout << "Number of Children: ";
	cin >> i;
	struct Node *prev = nullptr, *next;
	while (i--) {
		next = createNode(node, (bool) i);
		if (prev != nullptr) prev->sibling = next;
		else node->child = next;
		prev = next;
	}
	return node;
}

void preorderTraversal(struct Node *root) {
	cout << root->key << " ";
	if (root->child != nullptr) preorderTraversal(root->child);
	if (root->hasSibling) preorderTraversal(root->sibling);
}

void postorderTraversal(struct Node *root) {
	if (root->child != nullptr) postorderTraversal(root->child);
	cout << root->key << " ";
	if (root->hasSibling) postorderTraversal(root->sibling);
}

int main() {
	struct Node *root = createNode(nullptr, 0);
	cout << "Preorder Traversal: ";
	preorderTraversal(root);
	cout << endl;
	cout << "Postorder Traversal: ";
	postorderTraversal(root);
	cout << endl;
	return 0;
}
