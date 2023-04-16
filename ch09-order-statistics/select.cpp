#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &A, int p, int q, int m) {
	/* Partition Around m */
	int i;
	for (i = p; i < q; i++) {
		if (A[i] == m) {
			swap(A[i], A[q]);
			break;
		}
	}

	i = p;
	for (int j = p; j < q; j++) {
		if (A[j] <= A[q]) {
			swap(A[i], A[j]);
			i++;
		}
	}
	swap(A[i], A[q]);
	return i+1;
}

int median(vector<int> &A, int p, int q) {
	/* Base Case Median Using Insertion Sort */
	for (int i = p+1; i <= q; i++)
		for (int j = i; j > p, A[j-1] > A[j]; j--)
			swap(A[j-1], A[j]);
	return A[p+((q-p)/2)];
}

int select(vector<int> &A, int p, int q, int i) {
	int k, m, n = q-p+1;
	vector<int> M;
	M.reserve((n+4)/5);
	
	for (k = 0; k < n/5; k++) 
		M[k] = median(A, p+k*5, p+k*5+4);
	if ((n+4)/5 > n/5) M[n/5] = median(A, p+(n/5)*5, q);

	if (n>5) m = select(M, 0, ((n+4)/5)-1, ((n-1)/5));
	else m = M[0];

	k = partition(A, p, q, m);
	k -= p;
	
	if (i == k) return A[p+k-1];
	if (i < k) return select(A, p, p+k-2, i);
	return select(A, p+k, q, i-k);
}

int main() {
	int n, i, k;
	cout << "Number of Elements: ";
	cin >> n;
	vector<int> A(n);
	cout << "Elements: ";
	for (i = 0; i < n; i++) cin >> A[i];
	cout << "Order Statistic: ";
	cin >> i;

	cout << select(A, 0, n-1, i) << endl;
}
