#include <iostream>
#include <algorithm>
#include <climits>
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
};

class MinHeap {
	public:
		MinHeap(vector<pair<int,int>> D, int n);
		int size();
		bool empty();
		int peek(int u);
		pair<int,int> pop();
		void update(int u, int k);
	private:
		vector<pair<int,int>> A;
		vector<int> L;
		void heapify(int i);
		void build_min_heap();
		void decrease_key(int i, int k);
};

MinHeap::MinHeap(vector<pair<int,int>> D, int n) {
	A = D;
	L.resize(n, -1);
	for (int i = 0; i < D.size(); i++)
		L[D[i].second] = i;
	build_min_heap();
}

void MinHeap::heapify(int i) {
	int l = (i << 1) + 1;
	int r = (i << 1) + 2;
	int m = i;
	if (l < A.size() && A[m].first > A[l].first)
		m = l;
	if (r < A.size() && A[m].first > A[r].first)
		m = r;
	if (m != i) {
		swap(L[A[i].second], L[A[m].second]);
		swap(A[i], A[m]);
		heapify(m);
	}
}

void MinHeap::build_min_heap() {
	for (int i = (A.size() - 2) >> 1; i >= 0; i--)
		heapify(i);
}

int MinHeap::size() {
	return A.size();
}

bool MinHeap::empty() {
	return A.empty();
}

int MinHeap::peek(int u) {
	if (u >= L.size())
		__throw_out_of_range("Argument out of range.");
	if (L[u] == -1)
		__throw_invalid_argument("Element not in heap.");
	return A[L[u]].first;
}

pair<int,int> MinHeap::pop() {
	if (A.size() < 1)
		__throw_underflow_error("The heap is empty.");
	pair<int,int> max = A[0];
	L[A[0].second] = -1;
	L[A[A.size() - 1].second] = 0;
	A[0] = A[A.size() - 1];
	A.pop_back();
	heapify(0);
	return max;
}

void MinHeap::decrease_key(int i, int k) {
	if (k >= A[i].first)
		__throw_logic_error("New key is larger than the current key.");
	A[i].first = k;
	while (i > 0 && A[i].first < A[(i - 1) >> 1].first) {
		swap(L[A[i].second], L[A[(i - 1) >> 1].second]);
		swap(A[i], A[(i - 1) >> 1]);
		i = (i - 1) >> 1;
	}
}

void MinHeap::update(int u, int k) {
	if (u >= L.size())
		__throw_out_of_range("Argument out of range.");
	if (L[u] == -1)
		__throw_invalid_argument("Element not in heap.");
	decrease_key(L[u], k);
}

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

class Graph {
	friend istream& operator>>(istream& os, Graph& G);
	friend ostream& operator<<(ostream& os, const Graph& G);
	public:
		Graph(int n);
		void kruskal();
		void prim(int r);
	private:
		vector<list<pair<int,int>>> A;
};

Graph::Graph(int n) {
	A.resize(n);
}

istream& operator>>(istream& in, Graph& G) {
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

ostream& operator<<(ostream& out, const Graph& G) {
	for (int i = 0; i < G.A.size(); i++) {
		out << i << ": ";
		for (pair<int,int> v: G.A[i])
			out << "(" << v.first << "," << v.second << ") ";
		out << endl;
	}
	return out;
}

void Graph::kruskal() {
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
		int m = S.find_set(e.u);
		int n = S.find_set(e.v);
		if (m != n) {
			S.link_set(m, n);
			T.push_back(e);
		}
	}

	for (edge e: T)
		cout << e << endl;
}

void Graph::prim(int r) {
	if (r < 0 || A.size() <= r)
		return;

	vector<pair<int,int>> keys(A.size());
	vector<int> inqueue(A.size(), 1);
	vector<int> pred(A.size(), -1);
	vector<edge> T;

	for (int i = 0; i < A.size(); i++)
		keys[i] = make_pair(INT_MAX, i);
	keys[r].first = 0;
	MinHeap Q(keys, A.size());

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

int main() {
	int n;
	char op;
	cout << "Number of Vertices: ";
	cin >> n;
	Graph G(n);
	cout << "Edges: " << endl;
	while (cin >> G);
	cin.clear();
	clearerr(stdin);

	cout << "Choose an operation (k/p/P): ";
	while (cin >> op) {		
		if (op == 'k') {
			G.kruskal();
		} else if (op == 'p') {
			cout << G;
		} else if (op == 'P') {
			cout << "Starting Vertex: ";
			cin >> n;
			G.prim(n);
		} else cout << "Invalid response." << endl;
		cout << "Choose an operation (k/p/P): ";
	}
	cout << endl;

	return 0;
}
