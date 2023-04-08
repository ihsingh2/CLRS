#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &A, int p, int q) {
	int i = p;
	for (int j = p; j < q; j++) {
		if (A[j] <= A[q]) {
			swap(A[i], A[j]);
			i++;
		}
	}
	swap(A[i], A[q]);
	return i;
}

int randpartition(vector<int>& A, int p, int r) {
	int i = rand() % (r-p+1) + p;
	swap(A[i], A[r]);
	return partition(A, p, r);
}

int main() {
	int n, i, q, k;
	cout << "Enter the number of elements: ";
	cin >> n;
	vector<int> A;
	A.reserve(n);
	int p = 0, r = n-1;
	cout << "Enter the set of elements: ";
	for (i = 0; i < n; i++) cin >> A[i];
	cout << "Enter the order statistic to find: ";
	cin >> i;

	while (true) {
		if (p == r) {
			cout << A[p] << endl;
			return 0;
		}
		q = randpartition(A, p, r);
		k = q-p+1;
		if (i == k) {
			cout << A[q] << endl;
			return 0;
		}
		if (i < k) r = q-1;
		else {
			p = q+1;
			i -= k;
		}
	}
}
