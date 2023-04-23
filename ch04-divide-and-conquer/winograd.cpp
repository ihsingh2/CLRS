#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

size_t len(int n) {
	ostringstream strs;
	strs << n;
	return strs.str().size();
}

void add(vector<vector<int>>& C, vector<vector<int>>& A, vector<vector<int>>& B, int Ci, int Cj, int Ai, int Aj, int Bi, int Bj, int dim) {
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			C[Ci + i][Cj + j] = A[Ai + i][Aj + j] + B[Bi + i][Bj + j];
}

void subtract(vector<vector<int>>& C, vector<vector<int>>& A, vector<vector<int>>& B, int Ci, int Cj, int Ai, int Aj, int Bi, int Bj, int dim) {
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			C[Ci + i][Cj + j] = A[Ai + i][Aj + j] - B[Bi + i][Bj + j];
}

void winograd(vector<vector<int>>& C, vector<vector<int>>& A, vector<vector<int>>& B, int Ci, int Cj, int Ai, int Aj, int Bi, int Bj, int dim) {
	if (dim == 1) {
		C[Ci][Cj] = A[Ai][Aj] * B[Bi][Bj];
		return;
	}

	int qdim = dim >> 1;
	vector<vector<int>> T1(qdim, vector<int> (qdim));
	vector<vector<int>> T2(qdim, vector<int> (qdim));

	subtract(T1, A, A, 0, 0, Ai, Aj, Ai + qdim, Aj, qdim);
	subtract(T2, B, B, 0, 0, Bi + qdim, Bj + qdim, Bi, Bj + qdim, qdim);
	winograd(C, T1, T2, Ci + qdim, Cj, 0, 0, 0, 0, qdim);
	add(T1, A, A, 0, 0, Ai + qdim, Aj, Ai + qdim, Aj + qdim, qdim);
	subtract(T2, B, B, 0, 0, Bi, Bj + qdim, Bi, Bj, qdim);
	winograd(C, T1, T2, Ci + qdim, Cj + qdim, 0, 0, 0, 0, qdim);
	subtract(T1, T1, A, 0, 0, 0, 0, Ai, Aj, qdim);
	subtract(T2, B, T2, 0, 0, Bi + qdim, Bj + qdim, 0, 0, qdim);
	winograd(C, T1, T2, Ci, Cj, 0, 0, 0, 0, qdim);
	subtract(T1, A, T1, 0, 0, Ai, Aj + qdim, 0, 0, qdim);
	winograd(C, T1, B, Ci, Cj + qdim, 0, 0, Bi + qdim, Bj + qdim, qdim);
	add(C, C, C, Ci, Cj + qdim, Ci + qdim, Cj + qdim, Ci, Cj + qdim, qdim);
	winograd(T1, A, B, 0, 0, Ai, Aj, Bi, Bj, qdim);
	add(C, C, T1, Ci, Cj, Ci, Cj, 0, 0, qdim);
	add(C, C, C, Ci, Cj + qdim, Ci, Cj, Ci, Cj + qdim, qdim);
	add(C, C, C, Ci, Cj, Ci, Cj, Ci + qdim, Cj, qdim);
	subtract(T2, T2, B, 0, 0, 0, 0, Bi + qdim, Bj, qdim);
	winograd(C, A, T2, Ci + qdim, Cj, Ai + qdim, Aj + qdim, 0, 0, qdim);
	subtract(C, C, C, Ci + qdim, Cj, Ci, Cj, Ci + qdim, Cj, qdim);
	add(C, C, C, Ci + qdim, Cj + qdim, Ci, Cj, Ci + qdim, Cj + qdim, qdim);
	winograd(C, A, B, Ci, Cj, Ai, Aj + qdim, Bi + qdim, Bj, qdim);
	add(C, T1, C, Ci, Cj, 0, 0, Ci, Cj, qdim);
}

int main() {
	pair<int, int> d1, d2;
	cout << "Dimension of first matrix: ";
	cin >> d1.first >> d1.second;
	cout << "Dimension of second matrix: ";
	cin >> d2.first >> d2.second;

	if (d1.second != d2.first) {
		cout << "Incompatible dimensions." << endl;
		return 0;
	}
	int d, m = max(max(d1.first, d1.second), d2.second);
	if (m <= 2)
		d = m;
	else
		d = (1ULL << 32) >> __builtin_clz(m - 1);

	vector<vector<int>> A(d, vector<int> (d, 0));
	vector<vector<int>> B(d, vector<int> (d, 0));
	vector<vector<int>> C(d, vector<int> (d));
	cout << "First matrix: ";
	for (int i = 0; i < d1.first; i++)
		for (int j = 0; j < d1.second; j++) 
			cin >> A[i][j];
	cout << "Second matrix: ";
	for (int i = 0; i < d2.first; i++)
		for (int j = 0; j < d2.second; j++) 
			cin >> B[i][j];
	
	winograd(C, A, B, 0, 0, 0, 0, 0, 0, d);
	size_t collen[d2.second];
	for (int j = 0; j < d2.second; j++) {
		size_t maxlen;
		for (int i = 0; i < d1.first; i++)
			maxlen = max(maxlen, len(C[i][j]));
		collen[j] = maxlen;
	}
	for (int i = 0; i < d1.first; i++) {
		for (int j = 0; j < d2.second; j++)
			cout << setw(collen[j]) << C[i][j] << " ";
		cout << endl;
	}
	return 0;
}
