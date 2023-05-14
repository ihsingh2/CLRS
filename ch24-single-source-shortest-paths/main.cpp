#include <iostream>
#include "weighted_directed_graph.h"
using namespace std;

int main() {
	int n;
	char op;
	cout << "Number of Vertices: ";
	cin >> n;
	WeightedDirectedGraph G(n);
	cout << "Edges: " << endl;
	while (cin >> G);
	cin.clear();
	clearerr(stdin);

	cout << "Choose an operation (b/d/i/j/p/t): ";
	while (cin >> op) {

		if (op == 'b') {
			cout << "Source: ";
			cin >> n;
			try {
				G.bellman_ford(n);
			} catch (logic_error e) {
				cout << e.what() << endl;
			}
		} 
		else if (op == 'd') {
			cout << "Source: ";
			cin >> n;
			G.dijkstra(n);
		} 
		else if (op == 'i') {
			try {
				G.minimum_incoming_path();
			} catch (logic_error e) {
				cout << e.what() << endl;
			}
		}
		else if (op == 'j')
			G.johnson();
		else if (op == 'p')
			cout << G;
		else if (op == 't') {
			cout << "Source: ";
			cin >> n;
			try {
				G.tsort_shortest_path(n);
			} catch (logic_error e) {
				cout << e.what() << endl;
			}
		}
		else 
			cout << "Invalid response." << endl;

		cout << "Choose an operation (b/d/i/j/p/t): ";
	}
	cout << endl;

	return 0;
}
