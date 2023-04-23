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

void strassen(vector<vector<int>>& C, vector<vector<int>>& A, vector<vector<int>>& B, int Ci, int Cj, int Ai, int Aj, int Bi, int Bj, int dim) {
	if (dim == 1) {
		C[Ci][Cj] = A[Ai][Aj] * B[Bi][Bj];
		return;
	}

	int qdim = dim >> 1;
	vector<vector<int>> T1(qdim, vector<int> (qdim));
	vector<vector<int>> T2(qdim, vector<int> (qdim));

	subtract(C, A, A, Ci, Cj + qdim, Ai + qdim, Aj, Ai, Aj, qdim);
	add(C, B, B, Ci + qdim, Cj, Bi, Bj, Bi, Bj + qdim, qdim);
	strassen(C, C, C, Ci + qdim, Cj + qdim, Ci, Cj + qdim, Ci + qdim, Cj, qdim);
	subtract(C, A, A, Ci, Cj + qdim, Ai, Aj + qdim, Ai + qdim, Aj + qdim, qdim);
	add(C, B, B, Ci + qdim, Cj, Bi + qdim, Bj, Bi + qdim, Bj + qdim, qdim);
	strassen(C, C, C, Ci, Cj, Ci, Cj + qdim, Ci + qdim, Cj, qdim);
	add(C, A, A, Ci, Cj + qdim, Ai, Aj, Ai + qdim, Aj + qdim, qdim);
	add(C, B, B, Ci + qdim, Cj, Bi, Bj, Bi + qdim, Bj + qdim, qdim);
	strassen(T1, C, C, 0, 0, Ci, Cj + qdim, Ci + qdim, Cj, qdim);
	add(C, T1, C, Ci, Cj, 0, 0, Ci, Cj, qdim);
	add(C, T1, C, Ci + qdim, Cj + qdim, 0, 0, Ci + qdim, Cj + qdim, qdim);
	add(T2, A, A, 0, 0, Ai + qdim, Aj, Ai + qdim, Aj + qdim, qdim);
	strassen(C, T2, B, Ci + qdim, Cj, 0, 0, Bi, Bj, qdim);
	subtract(C, C, C, Ci + qdim, Cj + qdim, Ci + qdim, Cj + qdim, Ci + qdim, Cj, qdim);
	subtract(T1, B, B, 0, 0, Bi + qdim, Bj, Bi, Bj, qdim);
	strassen(T2, A, T1, 0, 0, Ai + qdim, Aj + qdim, 0, 0, qdim);
	add(C, C, T2, Ci + qdim, Cj, Ci + qdim, Cj, 0, 0, qdim);
	add(C, C, T2, Ci, Cj, Ci, Cj, 0, 0, qdim);
	subtract(T1, B, B, 0, 0, Bi, Bj + qdim, Bi + qdim, Bj + qdim, qdim);
	strassen(C, A, T1, Ci, Cj + qdim, Ai, Aj, 0, 0, qdim);
	add(C, C, C, Ci + qdim, Cj + qdim, Ci + qdim, Cj + qdim, Ci, Cj + qdim, qdim);
	add(T2, A, A, 0, 0, Ai, Aj, Ai, Aj + qdim, qdim);
	strassen(T1, T2, B, 0, 0, 0, 0, Bi + qdim, Bj + qdim, qdim);
	add(C, C, T1, Ci, Cj + qdim, Ci, Cj + qdim, 0, 0, qdim);
	subtract(C, C, T1, Ci, Cj, Ci, Cj, 0, 0, qdim);	
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
	
	strassen(C, A, B, 0, 0, 0, 0, 0, 0, d);
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
