#pragma once
#include <list>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

class DirectedGraph {
	friend istream& operator>>(istream& os, DirectedGraph& G);
	friend ostream& operator<<(ostream& os, const DirectedGraph& G);
	public:
		DirectedGraph(int n);
		void bfs(int s);
		void dfs();
		void dfs_edges();
		void tsort_dfs();
		void tsort_kahn();
		int count_simple_paths(int s, int t);
		void ssc_kosaraju();
		void ssc_tarjan();
		void euler_tour();
		void reachability();
		void transpose();
		void simplify();
		void square();
		int universal_sink();
	private:
		vector<list<int>> A;
		vector<int> indeg;
		void dfs_edges_child(vector<int>& visited, vector<int>& disc, vector<int>& pred, int& time, int u);
		void strong_connect(int v, int& id, stack<int>& S, vector<int>& index, vector<int>& lowlink, vector<int>& onstack);
		void radix_sort(vector<pair<int,int>>& A, int d);
};
