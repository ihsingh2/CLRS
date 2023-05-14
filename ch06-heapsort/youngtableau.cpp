#include <climits>
#include <iomanip>
#include <sstream>
#include "youngtableau.h"

size_t len(int n) {
	ostringstream strs;
	strs << n;
	return strs.str().size();
}

ostream& operator<<(ostream& out, const YoungTableau& Y) {
	size_t collen[Y.n];
	for (int j = 0; j < Y.n; j++) {
		size_t maxlen = 0;
		for (int i = 0; i < Y.m; i++) {
			if (Y.A[i][j] != INT_MAX)
				maxlen = max(maxlen, len(Y.A[i][j]));
			else {
				maxlen = max(maxlen, len(0));
				break;
			}
		}
		collen[j] = maxlen;
	}

	for (int i = 0; i < Y.m; i++) {
		for (int j = 0; j < Y.n; j++) {
			if (Y.A[i][j] == INT_MAX)
				out << setw(collen[j]) << "." << " ";
			else
				out << setw(collen[j]) << Y.A[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

YoungTableau::YoungTableau(int r, int c) {
	m = r;
	n = c;
	for (int i=0; i<r; i++)
		A.push_back(vector<int>(c, INT_MAX));
}

int YoungTableau::extract_min() {
	if (A[0][0] == INT_MAX)
		__throw_underflow_error("The tableau is empty.");
	int i = 0, j = 0, k = A[0][0];
	A[0][0] = INT_MAX;
	while (i < m && j < n) {
		int d = INT_MAX, r = INT_MAX;
		if (i < m-1) d = A[i+1][j];
		if (j < n-1) r = A[i][j+1];

		if (d == INT_MAX && r == INT_MAX) break;
		if (d < r) {
			swap(A[i][j], A[i+1][j]);
			i++;
		}
		else {
			swap(A[i][j], A[i][j+1]);
			j++;
		}
	}
	return k;
}

void YoungTableau::insert(int k) {
	if (A[m-1][n-1] != INT_MAX)
		__throw_overflow_error("The tableau is full.");
	A[m-1][n-1] = k;

	int i = m-1, j = n-1;
	while (i >= 0 && j>=0) {
		int u = INT_MIN, l = INT_MIN;
		if (i > 0) u = A[i-1][j];
		if (j > 0) l = A[i][j-1];

		if (k >= u && k >= l) break;
		if (u >= l) {
			swap(A[i][j], A[i-1][j]);
			i--;
		} else {
			swap(A[i][j], A[i][j-1]);
			j--;
		}
	}
}

pair<int,int> YoungTableau::find(int k) {
	int i = 0, j = n-1;
	while (i < m && j >= 0) {
		if (A[i][j] == k)
			return make_pair(i,j);
		if (A[i][j] > k)
			j--;
		else
			i++;
	}
	__throw_logic_error("Element not found.");
}

vector<int> YoungTableau::sort() {
	vector<vector<int>> B = A;
	vector<int> C;
	try {
		for (int i=0; i<m*n; i++) {
			C.push_back(extract_min());
		}
	} catch (underflow_error e) {}
	A = B;
	return C;
}
