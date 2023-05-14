#include <iostream>
#include "directedgraph.h"
using namespace std;

int main() {
	int m, n;
	char op;
	cout << "Number of Vertices: ";
	cin >> n;
	DirectedGraph G(n);
	cout << "Edges: " << endl;
	while (cin >> G);
	cin.clear();
	clearerr(stdin);

	cout << "Choose an operation (b/c/d/D/e/k/K/n/p/r/s/S/t/T/u): ";
	while (cin >> op) {

		if (op == 'b') {
			cout << "Source: ";
			cin >> m;
			G.bfs(m);
		} 
		else if (op == 'c') {
			cout << "Enter the two vertices: ";
			cin >> m >> n;
			cout << G.count_simple_paths(m, n) << endl;
		} 
		else if (op == 'd')
			G.dfs();
		else if (op == 'D')
			G.dfs_edges();
		else if (op == 'e')
			G.euler_tour();
		else if (op == 'k')
			G.tsort_kahn();
		else if (op == 'K')
			G.ssc_kosaraju();
		else if (op == 'n')
			G.transpose();
		else if (op == 'p')
			cout << G;
		else if (op == 'r')
			G.reachability();
		else if (op == 's')
			G.simplify();
		else if (op == 'S')
			G.square();
		else if (op == 't')
			G.tsort_dfs();
		else if (op == 'T')
			G.ssc_tarjan();
		else if (op == 'u') {
			m = G.universal_sink();
			if (m != -1)
				cout << m << endl;
		} 
		else
			cout << "Invalid response." << endl;

		cout << "Choose an operation (b/c/d/D/e/k/K/n/p/r/s/S/t/T/u): ";
	}
	cout << endl;

	return 0;
}
