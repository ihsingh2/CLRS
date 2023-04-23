#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct DisjointSet {
	vector<int> rank;
	vector<int> parent;
	vector<list<int>> set;

	DisjointSet(int n) {
		rank.resize(n, 0);
		parent.resize(n);
		set.resize(n);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			set[i].push_back(i);
		}
	}

	int find_set(int x) {
		if (x != parent[x])
			parent[x] = find_set(parent[x]);
		return parent[x];
	}
	
	void link_set(int x, int y) {
		if (rank[x] > rank[y]) {
			parent[y] = x;
			set[x].splice(set[x].end(), set[y]);
		}
		else {
			parent[x] = y;
			set[y].splice(set[y].end(), set[x]);
			if (rank[x] == rank[y])
				rank[y]++;
		}
	}

	void union_set(int x, int y) {
		link_set(find_set(x), find_set(y));
	}

	void print_set(int x) {
		int r = find_set(x);
		for (auto y: set[r])
			cout << y << " ";
		cout << endl;
	}
};

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
			cout << S.find_set(n) << endl;
		} else if (op == 'p') {
			cout << "Element: ";
			cin >> n;
			S.print_set(n);
		} else if (op == 'u') {
			cout << "Elements: ";
			cin >> m >> n;
			S.union_set(m, n);
		} else cout << "Invalid response." << endl;
		cout << "Choose an operation (f/p/u): ";
	}
	cout << endl;

	return 0;
}