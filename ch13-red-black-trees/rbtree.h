#pragma once
#include <iostream>
using namespace std;

template <class T>
class RedBlackTreeNode {
	public:
		T key;
		int color;
		RedBlackTreeNode<T> *parent;
		RedBlackTreeNode<T> *left;
		RedBlackTreeNode<T> *right;
};

template <class T>
class RedBlackTree {
	public:
		RedBlackTree();
		~RedBlackTree();
		void insert_key(T k);
		void delete_key(T k);
		void inorder_walk();
		void postorder_walk();
	private:
		RedBlackTreeNode<T> *root;
		RedBlackTreeNode<T> *NIL;
		RedBlackTreeNode<T>* get_min(RedBlackTreeNode<T> *x);
		RedBlackTreeNode<T>* get_max(RedBlackTreeNode<T> *x);
		RedBlackTreeNode<T>* get_succ(RedBlackTreeNode<T> *x);
		RedBlackTreeNode<T>* get_pred(RedBlackTreeNode<T> *x);
		RedBlackTreeNode<T>* search_key(T k);
		void transplant(RedBlackTreeNode<T> *u, RedBlackTreeNode<T> *v);
		void left_rotate(RedBlackTreeNode<T> *x);
		void right_rotate(RedBlackTreeNode<T> *y);
		void insert_fixup(RedBlackTreeNode<T> *z);
		void delete_fixup(RedBlackTreeNode<T> *x);
		void inorder_traversal(RedBlackTreeNode<T> *x);
		void postorder_traversal(RedBlackTreeNode<T> *x);
		void postorder_deletion(RedBlackTreeNode<T> *x);
};

static const int RED = 0;
static const int BLACK = 1;

template <class T>
RedBlackTree<T>::RedBlackTree() {
	NIL = new RedBlackTreeNode<T>;
	NIL->color = BLACK;
	root = NIL;
}

template<class T>
RedBlackTree<T>::~RedBlackTree() {
	if (root != NIL)
		postorder_deletion(root);
	delete NIL;
}

template <class T>
RedBlackTreeNode<T>* RedBlackTree<T>::get_min(RedBlackTreeNode<T> *x) {
	while (x->left != NIL)
		x = x->left;
	return x;
}

template <class T>
RedBlackTreeNode<T>* RedBlackTree<T>::get_max(RedBlackTreeNode<T> *x) {
	while (x->right != NIL)
		x = x->right;
	return x;
}

template <class T>
RedBlackTreeNode<T>* RedBlackTree<T>::get_succ(RedBlackTreeNode<T> *x) {
	if (x->right != NIL)
		return get_min(x->right);
	RedBlackTreeNode<T> *y = x->parent;
	while (y != NIL && y->right == x) {
		x = y;
		y = y->parent;
	}
	return y;
}

template <class T>
RedBlackTreeNode<T>* RedBlackTree<T>::get_pred(RedBlackTreeNode<T> *x) {
	if (x->left != NIL)
		return get_min(x->left);
	RedBlackTreeNode<T> *y = x->parent;
	while (y != NIL && y->left == x) {
		x = y;
		y = y->parent;
	}
	return y;
}

template <class T>
RedBlackTreeNode<T>* RedBlackTree<T>::search_key(T k) {
	RedBlackTreeNode<T> *node = root;
	while (node != NIL) {
		if (node->key > k)
			node = node->left;
		else if (node->key == k)
			break;
		else
			node = node->right;
	}
	return node;
}

template <class T>
void RedBlackTree<T>::transplant(RedBlackTreeNode<T> *u, RedBlackTreeNode<T> *v) {
	if (u->parent == NIL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else 
		u->parent->right = v;
	v->parent = u->parent;
}

template <class T>
void RedBlackTree<T>::left_rotate(RedBlackTreeNode<T> *x) {
	RedBlackTreeNode<T> *y = x->right;

	x->right = y->left;
	if (y->left != NIL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NIL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

template <class T>
void RedBlackTree<T>::right_rotate(RedBlackTreeNode<T> *y) {
	RedBlackTreeNode<T> *x = y->left;
	
	y->left = x->right;
	if (x->right != NIL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NIL)
		root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}

template <class T>
void RedBlackTree<T>::insert_key(T k) {
	RedBlackTreeNode<T> *z = new RedBlackTreeNode<T>;
	RedBlackTreeNode<T> *x = root;
	RedBlackTreeNode<T> *y = NIL;
	while (x != NIL) {
		y = x;
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == NIL)
		root = z;
	else if (y->key > k)
		y->left = z;
	else y->right = z;
	z->key = k;
	z->color = RED;
	z->left = NIL;
	z->right = NIL;
	insert_fixup(z);
}

template <class T>
void RedBlackTree<T>::insert_fixup(RedBlackTreeNode<T> *z) {
	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			RedBlackTreeNode<T> *y = z->parent->parent->right;
			// case 1
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				// case 2
				if (z == z->parent->right) {
					z = z->parent;
					left_rotate(z);
				}
				// case 3
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		}
		else {
			RedBlackTreeNode<T> *y = z->parent->parent->left;
			// case 1
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				// case 2
				if (z == z->parent->left) {
					z = z->parent;
					right_rotate(z);
				}
				// case 3
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

template <class T>
void RedBlackTree<T>::delete_key(T k) {
	RedBlackTreeNode<T> *x, *y, *z = search_key(k);
	if (z == NIL)
		__throw_logic_error("Key not found.");
	y = z;
	int ycolor = y->color;
	if (z->left == NIL) {
		x = z->right;
		transplant(z,z->right);
	} else if (z->right == NIL) {
		x = z->left;
		transplant(z,z->left);
	} else {
		y = get_min(z->right);
		ycolor = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else {
			transplant(y,y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z,y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (ycolor == BLACK)
		delete_fixup(x);
}

template <class T>
void RedBlackTree<T>::delete_fixup(RedBlackTreeNode<T> *x) {
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			RedBlackTreeNode<T> *w = x->parent->right;
			// case 1
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent);
				w = x->parent->right;
			}
			// case 2
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				// case 3
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					right_rotate(w);
					w = x->parent->right;
				}
				// case 4
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotate(x->parent);
				x = root;
			}
		}
		else {
			RedBlackTreeNode<T> *w = x->parent->left;
			// case 1
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate(x->parent);
				w = x->parent->left;
			}
			// case 2
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				// case 3
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					left_rotate(w);
					w = x->parent->left;
				}
				// case 4
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

template <class T>
void RedBlackTree<T>::inorder_walk() {
	if (root != NIL) {
		inorder_traversal(root);
		cout << endl;
	}
}

template <class T>
void RedBlackTree<T>::postorder_walk() {
	if (root != NIL) {
		postorder_traversal(root);
		cout << endl;
	}
}

template <class T>
void RedBlackTree<T>::inorder_traversal(RedBlackTreeNode<T> *node) {
	if (node == NIL)
		return;
	inorder_traversal(node->left);
	cout << node->key;
	if (node->color == RED)
		cout << "(R) ";
	else
		cout << "(B) ";
	inorder_traversal(node->right);
}

template <class T>
void RedBlackTree<T>::postorder_traversal(RedBlackTreeNode<T> *node) {
	if (node->left != NIL) 
		postorder_traversal(node->left);
	if (node->right != NIL) 
		postorder_traversal(node->right);
	cout << node->key;
	if (node->color == RED)
		cout << "(R) ";
	else
		cout << "(B) ";
}

template <class T>
void RedBlackTree<T>::postorder_deletion(RedBlackTreeNode<T> *node) {
	if (node->left != NIL) 
		postorder_deletion(node->left);
	if (node->right != NIL) 
		postorder_deletion(node->right);
	delete node;
}
