#include "disjointset.h"

DisjointSet::DisjointSet(int n) {
	size = n;
	rank.resize(n, 0);
	parent.resize(n);
	set.resize(n);
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		set[i].push_back(i);
	}
}

ostream& operator<<(ostream& out, const DisjointSet& S) {
	for (int i = 0; i < S.size; i++) {
		if (!S.set[i].empty()) {
			for (auto x : S.set[i])
				out << x << " ";
			out << endl;
		}
	}
	return out;
}

int DisjointSet::find_set(int x) {
	if (x < 0 || size <= x)
		__throw_out_of_range("Element not in disjoint set forest.");
	if (x != parent[x])
		parent[x] = find_set(parent[x]);
	return parent[x];
}

void DisjointSet::link_set(int x, int y) {
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

void DisjointSet::union_set(int x, int y) {
	if (0 <= x && x < size && 0 <= y && y < size)
		link_set(find_set(x), find_set(y));
	else
		__throw_out_of_range("Element not in disjoint set forest.");
}
