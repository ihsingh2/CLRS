#include <iostream>
#include "undirectedgraph.h"
using namespace std;

int main() {
	int n;
	char op;
	cout << "Number of Vertices: ";
	cin >> n;
	UndirectedGraph G(n);
	cout << "Edges: " << endl;
	while (cin >> G);
	cin.clear();
	clearerr(stdin);

	cout << "Choose an operation (k/o/p): ";
	while (cin >> op) {

		if (op == 'k')
			G.kruskal();
		else if (op == 'o')
			cout << G;
		else if (op == 'p') {
			cout << "Starting Vertex: ";
			cin >> n;
			G.prim(n);
		}
		else 
			cout << "Invalid response." << endl;
		
		cout << "Choose an operation (k/o/p): ";
	}
	cout << endl;

	return 0;
}
