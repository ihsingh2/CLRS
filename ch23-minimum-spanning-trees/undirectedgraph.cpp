#include <climits>
#include <algorithm>
#include "undirectedgraph.h"
#include "../ch06-heapsort/binaryheap.h"
#include "../ch21-disjoint-set-data-structures/disjointset.h"

struct edge {
	int u;
	int v;
	int w;
};

ostream& operator<<(ostream& out, const edge& e) {
	out << "(" << e.u << "," << e.v << "," << e.w << ")";
	return out;
}

bool compare_edges(const edge& e, const edge &f) {
	return e.w < f.w;
}

UndirectedGraph::UndirectedGraph(int n) {
	A.resize(n);
}

istream& operator>>(istream& in, UndirectedGraph& G) {
	edge temp;
	in >> temp.u >> temp.v >> temp.w;
	if (!in) 
		return in;
	if (0 <= temp.u && temp.u < G.A.size() && 0 <= temp.v && temp.v < G.A.size()) {
		G.A[temp.u].push_back(make_pair(temp.v, temp.w));
		G.A[temp.v].push_back(make_pair(temp.u, temp.w));
	}
	return in;
}

ostream& operator<<(ostream& out, const UndirectedGraph& G) {
	for (int i = 0; i < G.A.size(); i++) {
		out << i << ": ";
		for (pair<int,int> v: G.A[i])
			out << "(" << v.first << "," << v.second << ") ";
		out << endl;
	}
	return out;
}

void UndirectedGraph::kruskal() {
	vector<edge> E;
	vector<edge> T;
	DisjointSet S(A.size());

	for (int i = 0; i < A.size(); i++) {
		edge temp;
		temp.u = i;
		for (pair<int,int> j: A[i]) {
			temp.v = j.first;
			temp.w = j.second;
			E.push_back(temp);
		}
	}
	
	sort(E.begin(), E.end(), &compare_edges);

	for (edge e: E) {
		if (S.find_set(e.u) != S.find_set(e.v)) {
			S.union_set(e.u, e.v);
			T.push_back(e);
		}
	}

	for (edge e: T)
		cout << e << endl;
}

void UndirectedGraph::prim(int r) {
	if (r < 0 || A.size() <= r)
		return;

	vector<pair<int,int>> D(A.size());
	vector<int> inqueue(A.size(), 1);
	vector<int> pred(A.size(), -1);
	vector<edge> T;

	for (int i = 0; i < A.size(); i++)
		D[i] = make_pair(INT_MAX, i);
	D[r].first = 0;
	MinHeap Q(D);

	while (!Q.empty()) {
		pair<int,int> u = Q.pop();
		inqueue[u.second] = 0;

		edge temp;
		temp.u = pred[u.second];
		temp.v = u.second;
		temp.w = u.first;
		T.push_back(temp);

		for (pair<int,int> e: A[u.second]) {
			if (inqueue[e.first] == 1 && Q.peek(e.first) > e.second) {
				pred[e.first] = u.second;
				Q.update(e.first, e.second);
			}
		}
	}

	T.erase(T.begin());
	for (edge e: T)
		cout << e << endl;
}
