#include <queue>
#include <cmath>
#include <climits>
#include "directedgraph.h"

DirectedGraph::DirectedGraph(int n) {
	A.resize(n);
	indeg.resize(n, 0);
}

istream& operator>>(istream& in, DirectedGraph& G) {
	pair<int,int> temp;
	in >> temp.first >> temp.second;
	if (!in) return in;
	if (0 <= temp.first && temp.first < G.A.size() && 0 <= temp.second && temp.second < G.A.size()) {
		G.A[temp.first].push_back(temp.second);
		G.indeg[temp.second]++;
	}
	return in;
}

ostream& operator<<(ostream& out, const DirectedGraph& G) {
	for (int i = 0; i < G.A.size(); i++) {
		out << i << ": ";
		for (auto v: G.A[i])
			out << v << " ";
		out << endl;
	}
	return out;
}

void DirectedGraph::bfs(int s) {
	vector<int> visited(A.size(), 0);
	vector<int> distance(A.size(), INT_MAX);
	vector<int> pred(A.size(), -1);
	queue<int> Q;

	distance[s] = 0;
	Q.push(s);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (auto v: A[u])
			if (visited[v] == 0) {
				visited[v] = 1;
				distance[v] = distance[u] + 1;
				pred[v] = u;
				Q.push(v);
			}
		visited[u] = 1;
	}

	cout << "Distance: ";
	for (int i = 0; i < A.size(); i++) {
		if (distance[i] == INT_MAX)
			cout << ". ";
		else
			cout << distance[i] << " ";
	}
	cout << endl << "Predecessor: ";
	for (int i = 0; i < A.size(); i++) {
		if (pred[i] == -1)
			cout << ". ";
		else
			cout << pred[i] << " ";
	}
	cout << endl;
}

void DirectedGraph::dfs() {
	vector<int> visited(A.size(), 0);
	vector<int> disc(A.size());
	vector<int> finished(A.size());
	vector<int> pred(A.size(), -1);
	stack<int> S;
	int time = 0;

	for (int i = 0; i < A.size(); i++) {
		if (visited[i] == 0) {
			disc[i] = ++time;
			visited[i] = 1;
			S.push(i);
		}
		while (!S.empty()) {
			loopentry:
				int u = S.top();
				time += 1;
				for (auto v: A[u]) {
					if (visited[v] == 0) {
						visited[v] = 1;
						disc[v] = time;
						pred[v] = u;
						S.push(v);
						goto loopentry;
					}
				}
				finished[u] = time;
				S.pop();
		}
	}

	cout << "Discovery: ";
	for (int i = 0; i < A.size(); i++)
		cout << disc[i] << " ";
	cout << endl << "Finish Time: ";
	for (int i = 0; i < A.size(); i++)
		cout << finished[i] << " ";
	cout << endl << "Predecessor: ";
	for (int i = 0; i < A.size(); i++) {
		if (pred[i] == -1)
			cout << ". ";
		else
			cout << pred[i] << " ";
	}
	cout << endl;
}

void DirectedGraph::dfs_edges() {
	vector<int> visited(A.size(), 0);
	vector<int> disc(A.size());
	vector<int> pred(A.size(), -1);
	int time = 0;

	for (int i = 0; i < A.size(); i++) {
		if (visited[i] == 0) {
			disc[i] = ++time;
			visited[i] = 1;
			dfs_edges_child(visited, disc, pred, time, i);
		}
	}
}

void DirectedGraph::dfs_edges_child(vector<int>& visited, vector<int>& disc, vector<int>& pred, int& time, int u) {
	time++;	
	for (auto v: A[u]) {
		if (visited[v] == 0) {
			cout << "TREE EDGE: (" << u << "," << v << ")" << endl;
			visited[v] = 1;
			disc[v] = time;
			pred[v] = u;
			dfs_edges_child(visited, disc, pred, time, v);
		}
		else if (visited[v] == 1)
			cout << "BACK EDGE: (" << u << "," << v << ")" << endl;
		else if (disc[v] > disc[u])
			cout << "FORWARD EDGE: (" << u << "," << v << ")" << endl;
		else
			cout << "CROSS EDGE: (" << u << "," << v << ")" << endl;
	}
	visited[u] = 2;
}

void DirectedGraph::tsort_dfs() {
	vector<int> visited(A.size(), 0);
	list<int> sorted;
	stack<int> S;

	for (int i = 0; i < A.size(); i++) {
		if (visited[i] == 0) {
			visited[i] = 1;
			S.push(i);
		}
		while (!S.empty()) {
			loopentry:
				int u = S.top();
				for (auto v: A[u]) {
					if (visited[v] == 0) {
						visited[v] = 1;
						S.push(v);
						goto loopentry;
					}
					if (visited[v] == 1) {
						cout << "Topological Ordering does not exist." << endl;
						return;
					}
				}
				visited[u] = 2;
				sorted.push_front(u);
				S.pop();
		}
	}

	cout << "Topological Ordering: ";
	for (auto v: sorted)
		cout << v << " ";
	cout << endl;
}

void DirectedGraph::tsort_kahn() {
	vector<int> B = indeg;
	queue<int> Q;
	vector<int> sorted;
	sorted.reserve(indeg.size());
	for (int i = 0; i < indeg.size(); i++)
		if (indeg[i] == 0)
			Q.push(i);

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		sorted.push_back(u);
		for (auto v: A[u])
			if (--indeg[v] == 0)
				Q.push(v);
	}

	indeg = B;
	if (sorted.size() != indeg.size())
		cout << "Topological Ordering does not exist." << endl;
	else {
		cout << "Topological Ordering: ";
		for (int i = 0; i < sorted.size(); i++)
			cout << sorted[i] << " ";
		cout << endl;
	}
}

int DirectedGraph::count_simple_paths(int s, int t) {
	int	x, y;
	vector<int> B = indeg;
	queue<int> Q;
	vector<int> sorted;
	sorted.reserve(indeg.size());
	for (int i = 0; i < indeg.size(); i++)
		if (indeg[i] == 0)
			Q.push(i);
			
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if (u == s)
			x = sorted.size();
		if (u == t)
			y = sorted.size();
		sorted.push_back(u);
		for (auto v: A[u])
			if (--indeg[v] == 0)
				Q.push(v);
	}

	indeg = B;
	if (sorted.size() != indeg.size())
		__throw_logic_error("The graph contains cycle.");
	
	vector<int> paths(indeg.size(), 0);
	paths[t] = 1;
	for (int i = y-1; i >= x; i--) {
		int u = sorted[i];
		for (auto v: A[u])
			paths[u] += paths[v];
	}
	return paths[s];
}

void DirectedGraph::ssc_kosaraju() {
	vector<int> visited(A.size(), 0);
	vector<int> finished;
	stack<int> S;

	for (int i = 0; i < A.size(); i++) {
		if (visited[i] == 0) {
			visited[i] = 1;
			S.push(i);
		}
		while (!S.empty()) {
			firstloopentry:
				int u = S.top();
				for (auto v: A[u]) {
					if (visited[v] == 0) {
						visited[v] = 1;
						S.push(v);
						goto firstloopentry;
					}
				}
				finished.push_back(u);
				S.pop();
		}
	}

	vector<list<int>> C;
	vector<list<int>> T(A.size());
	for (int i = 0; i < A.size(); i++)
		for (auto j: A[i])
			T[j].push_back(i);
	fill(visited.begin(), visited.end(), 0);

	for (int i = A.size() - 1; i >= 0; i--) {
		int x = finished[i];
		if (visited[x] == 1)
			continue;
		list<int> component;
		visited[x] = 1;
		S.push(x);
		while (!S.empty()) {
			secondloopentry:
				int u = S.top();
				for (auto v: T[u]) {
					if (visited[v] == 0) {
						visited[v] = 1;
						S.push(v);
						goto secondloopentry;
					}
				}
				component.push_back(u);
				S.pop();
		}
		C.push_back(component);
	}

	for (int i = 0; i < C.size(); i++) {
		cout << "C" << i << ": ";
		for (auto x: C[i])
			cout << x << " ";
		cout << endl;
	}
}

void DirectedGraph::ssc_tarjan() {
	stack<int> S;
	int id = 0;
	vector<int> index(A.size(), -1);
	vector<int> lowlink(A.size(), 0);
	vector<int> onstack(A.size(), 0);

	for (int i = 0; i < A.size(); i++)
		if (index[i] == -1)
			strong_connect(i, id, S, index, lowlink, onstack);

	vector<list<int>> C(A.size());
	for (int i = 0; i < A.size(); i++)
		C[lowlink[i]].push_back(i);
	for (int i = 0, j = 0; i < A.size(); i++) {
		if (!C[i].empty()) {
			cout << "C" << j++ << ": ";
			for (auto x: C[i])
				cout << x << " ";
			cout << endl;
		}
	}
}

void DirectedGraph::strong_connect(int u, int& id, stack<int>& S, vector<int>& index, vector<int>& lowlink, vector<int>& onstack) {
	S.push(u);
	onstack[u] = 1;
	index[u] = lowlink[u] = id++;

	for (auto v: A[u]) {
		if (index[v] == -1)
			strong_connect(v, id, S, index, lowlink, onstack);
		if (onstack[v] == 1)
			lowlink[u] = min(lowlink[u], lowlink[v]);
	}

	if (index[u] == lowlink[u]) {
		while (!S.empty()) {
			int v = S.top();
			onstack[v] = 0;
			lowlink[v] = index[u];
			S.pop();
			if (v == u)
				break;
		}
	}
}

void DirectedGraph::euler_tour() {
	for (int i = 0; i < A.size(); i++) {
		if (indeg[i] != A[i].size()) {
			cout << "All vertices must have even degree." << endl;
			return;
		}
	}

	vector<list<int>> B = A;
	int u;
	for (u = 0; u < A.size() && A[u].empty(); u++);
	while (!A[u].empty()) {
		cout << u << "->";
		int v = A[u].front();
		A[u].pop_front();
		u = v;
	}
	cout << u << endl;
	A = B;
}

void DirectedGraph::reachability() {	
	vector<list<int>> T(A.size());
	vector<int> minreach(A.size());
	vector<pair<int,int>> label(A.size());

	for (int i = 0; i < A.size(); i++) {
		minreach[i] = -1;
		for (auto j: A[i])
			T[j].push_back(i);
	}

	int d = 1;
	cout << "Labels: ";
	for (int i = 0; i < A.size(); i++) {
		cin >> label[i].first;
		label[i].second = i;
		d = max(d, label[i].first/10 + 1);
	}
	radix_sort(label, d);

	for (int i = 0; i < A.size(); i++) {
		int u = label[i].second;
		if (minreach[u] == -1)
			minreach[u] = u;
		for (auto v: T[u])
			if (minreach[v] == -1)
				minreach[v] = minreach[u];
	}

	cout << "Min Reach: ";
	for (int i = 0; i < A.size(); i++)
		cout << minreach[i] << " ";
	cout << endl;
}

void DirectedGraph::radix_sort(vector<pair<int,int>>& A, int d) {
	int i, j, k = 10, n = A.size();
	vector<pair<int,int>> B(n);

	for (j = 0; j < d; j++) {
		vector<int> C(k, 0);
		int p = pow(k, j);
		if (j % 2) {
			// consider B as the intermediate input array
			for (i = 0; i < n; i++)
				C[B[i].first / p % k]++;
			for (i = 1; i < k; i++)
				C[i] = C[i] + C[i-1];
			for (i = n-1; i >= 0; i--) {
				A[C[B[i].first / p % k]-1] = B[i];
				C[B[i].first / p % k]--;
			}
		} else {
			// consider A as the intermediate input array
			for (i = 0; i < n; i++)
				C[A[i].first / p % k]++;
			for (i = 1; i < k; i++)
				C[i] = C[i] + C[i-1];
			for (i = n-1; i >= 0; i--) {
				B[C[A[i].first / p % k]-1] = A[i];
				C[A[i].first / p % k]--;
			}
		}
	}

	if (d % 2)
		for (i = 0; i < n; i++)
			A[i] = B[i];
}

void DirectedGraph::transpose() {
	vector<list<int>> T(A.size());
	for (int i = 0; i < A.size(); i++) {
		indeg[i] = A[i].size();
		for (auto j: A[i])
			T[j].push_back(i);
	}
	A = T;
}

void DirectedGraph::simplify() {
	vector<list<int>> S(A.size());
	vector<int> visited(A.size(), -1);
	fill(indeg.begin(), indeg.end(), 0);

	for (int i = 0; i < A.size(); i++) {
		for (auto j: A[i]) {
			if (visited[j] != i && j != i) {
				visited[j] = i;
				S[i].push_back(j);
				indeg[j]++;
			}
		}
	}
	A = S;
}

void DirectedGraph::square() {
	vector<list<int>> S(A.size());
	vector<int> visited(A.size(), -1);
	fill(indeg.begin(), indeg.end(), 0);

	for (int i = 0; i < A.size(); i++) {
		for (auto j: A[i]) {
			if (visited[j] == i)
				continue;
			visited[j] = i;
			S[i].push_back(j);
			indeg[j]++;
			for (auto k: A[j]) {
				if (visited[k] != i) {
					visited[k] = i;
					S[i].push_back(k);
					indeg[k]++;
				}
			}
		}
	}
	A = S;
}

int DirectedGraph::universal_sink() {
	for (int i = 0; i < A.size(); i++) {
		if (indeg[i] == A.size() - 1 && A[i].size() == 0)
			return i;
	}
	return -1;
}
