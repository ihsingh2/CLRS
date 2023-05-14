#include <stack>
#include <climits>
#include "weighted_directed_graph.h"
#include "../ch06-heapsort/binaryheap.h"

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

WeightedDirectedGraph::WeightedDirectedGraph(int n) {
	A.resize(n);
}

istream& operator>>(istream& in, WeightedDirectedGraph& G) {
	edge temp;
	in >> temp.u >> temp.v >> temp.w;
	if (!in) 
		return in;
	if (0 <= temp.u && temp.u < G.A.size() && 0 <= temp.v && temp.v < G.A.size())
		G.A[temp.u].push_back(make_pair(temp.v, temp.w));
	return in;
}

ostream& operator<<(ostream& out, const WeightedDirectedGraph& G) {
	for (int i = 0; i < G.A.size(); i++) {
		out << i << ": ";
		for (pair<int,int> v: G.A[i])
			out << "(" << v.first << "," << v.second << ") ";
		out << endl;
	}
	return out;
}

void WeightedDirectedGraph::bellman_ford(int s) {
	vector<int> distance(A.size(), INT_MAX);
	vector<int> pred(A.size(), -1);
	distance[s] = 0;

	for (int i = 1; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			if (distance[j] == INT_MAX)
				continue;
			for (pair<int,int> e: A[j]) {
				if (distance[e.first] > distance[j] + e.second) {
					distance[e.first] = distance[j] + e.second;
					pred[e.first] = j;
				}
			}
		}
	}

	for (int j = 0; j < A.size(); j++)
		for (pair<int,int> e : A[j])
			if (distance[e.first] > distance[j] + e.second)
				return negative_cycle(pred, e.first);

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

void WeightedDirectedGraph::negative_cycle(vector<int> &pred, int v) {
	vector<int> visited(A.size(), 0);
	while (visited[v] == 0) {
		visited[v] = 1;
		v = pred[v];
	}

	int x = v;
	cout << "Negative cycle detected: ";
	do {
		cout << v << " ";
		v = pred[v];
	} while (v != x);
	cout << endl;
}

void WeightedDirectedGraph::minimum_incoming_path() {
	vector<int> distance(A.size(), 0);
	vector<int> pred(A.size());
	for (int i = 0; i < A.size(); i++)
		pred[i] = i;

	for (int i = 1; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			for (pair<int,int> e: A[j]) {
				if (distance[e.first] > distance[j] + e.second) {
					distance[e.first] = distance[j] + e.second;
					pred[e.first] = j;
				}
			}
		}
	}

	for (int j = 0; j < A.size(); j++)
		for (pair<int,int> e: A[j])
			if (distance[e.first] > distance[j] + e.second)
				return negative_cycle(pred, e.first);

	cout << "Weights: ";
	for (int i = 0; i < A.size(); i++)
		cout << distance[i] << " ";
	cout << endl << "Predecessor: ";
	for (int i = 0; i < A.size(); i++) {
		if (pred[i] == i)
			cout << ". ";
		else
			cout << pred[i] << " ";
	}
	cout << endl;
}

void WeightedDirectedGraph::tsort_shortest_path(int s) {
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
				for (auto e: A[u]) {
					if (visited[e.first] == 0) {
						visited[e.first] = 1;
						S.push(e.first);
						goto loopentry;
					}
					if (visited[e.first] == 1) {
						cout << "Topological Ordering does not exist." << endl;
						return;
					}
				}
				visited[u] = 2;
				sorted.push_front(u);
				S.pop();
		}
	}

	vector<int> distance(A.size(), INT_MAX);
	vector<int> pred(A.size(), -1);
	distance[s] = 0;

	for (auto v: sorted) {
		if (distance[v] == INT_MAX)
			continue;
		for (pair<int,int> e: A[v]) {
			if (distance[e.first] > distance[v] + e.second) {
				distance[e.first] = distance[v] + e.second;
				pred[e.first] = v;
			}
		}
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

void WeightedDirectedGraph::dijkstra(int s) {
	vector<int> distance(A.size(), INT_MAX);
	vector<int> inqueue(A.size(), 1);
	vector<int> pred(A.size(), -1);
	vector<pair<int,int>> keys(A.size());
	for (int i = 0; i < A.size(); i++)
		keys[i] = make_pair(INT_MAX, i);
	keys[s].first = 0;
	MinHeap Q(keys);

	while (!Q.empty()) {
		pair<int,int> m = Q.pop();
		int u = m.second;
		distance[u] = m.first;
		inqueue[u] = 0;
		if (distance[u] == INT_MAX)
			break;

		for (pair<int,int> e : A[u]) {
			if (inqueue[e.first]) {
				if (Q.peek(e.first) > distance[u] + e.second) {
					Q.update(distance[u] + e.second, e.first);
					pred[e.first] = u;
				}
			}
		}
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

void WeightedDirectedGraph::johnson() {
	vector<list<pair<int,int>>> B = A;
	list<pair<int,int>> S;
	for (int i = 0; i < A.size(); i++)
		S.push_back(make_pair(i, 0));
	B.push_back(S);

	vector<int> distance(A.size(), INT_MAX);
	vector<int> pred(A.size(), -1);
	distance[A.size()] = 0;

	for (int i = 1; i < B.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			if (distance[j] == INT_MAX)
				continue;
			for (pair<int,int> e: B[j]) {
				if (distance[e.first] > distance[j] + e.second) {
					distance[e.first] = distance[j] + e.second;
					pred[e.first] = j;
				}
			}
		}
	}

	for (int j = 0; j < B.size(); j++)
		for (pair<int,int> e : B[j])
			if (distance[e.first] > distance[j] + e.second)
				return negative_cycle(pred, e.first);

	for (int i = 0; i < A.size(); i++)
		for (pair<int,int> &e : B[i])
			e.second += distance[i] - distance[e.first];

	vector<vector<int>> D(A.size(), vector<int> (A.size(), INT_MAX));
	vector<vector<int>> P(A.size(), vector<int> (A.size(), -1));

	for (int i = 0; i < A.size(); i++) {
		vector<int> inqueue(A.size(), 1);	
		vector<pair<int,int>> keys(A.size());
		for (int j = 0; j < A.size(); j++)
			keys[j] = make_pair(INT_MAX, j);
		keys[i].first = 0;
		MinHeap Q(keys);

		while (!Q.empty()) {
			pair<int,int> m = Q.pop();
			int u = m.second;
			D[i][u] = m.first;
			inqueue[u] = 0;
			if (D[i][u] == INT_MAX)
				break;

			for (pair<int,int> e : B[u]) {
				if (inqueue[e.first]) {
					if (Q.peek(e.first) > D[i][u] + e.second) {
						Q.update(D[i][u] + e.second, e.first);
						P[i][e.first] = u;
					}
				}
			}
		}

		for (int j = 0; j < A.size(); j++)
			if (D[i][j] != INT_MAX)
				D[i][j] += distance[j] - distance[i];
	}
	
	cout << "Distance: " << endl;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			if (D[i][j] == INT_MAX)
				cout << ". ";
			else
				cout << D[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Predecessor: " << endl;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			if (P[i][j] == -1)
				cout << ". ";
			else
				cout << P[i][j] << " ";
		}
		cout << endl;
	}
}
