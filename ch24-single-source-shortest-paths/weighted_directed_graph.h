#pragma once
#include <list>
#include <vector>
#include <iostream>
using namespace std;

class WeightedDirectedGraph {
	friend istream& operator>>(istream& os, WeightedDirectedGraph& G);
	friend ostream& operator<<(ostream& os, const WeightedDirectedGraph& G);
	public:
		WeightedDirectedGraph(int n);
		void bellman_ford(int s);
		void minimum_incoming_path();
		void tsort_shortest_path(int s);
		void djikstra(int s);
	private:
		vector<list<pair<int,int>>> A;
		void negative_cycle(vector<int> &pred, int v);
};
