#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	int i, j, k = 10, n, d;
	cout << "Number of Elements: ";
	cin >> n;
	vector<int> A(n), B(n);
	cout << "Number of Digits: ";
	cin >> d;
	cout << "Elements: ";
	for (i = 0; i < n; i++)
		cin >> A[i];

	for (j = 0; j < d; j++) {
		vector<int> C(k, 0);
		int p = pow(k, j);
		if (j % 2) {
			// consider B as the intermediate input array
			for (i = 0; i < n; i++)
				C[B[i] / p % k]++;
			for (i = 1; i < k; i++)
				C[i] = C[i] + C[i-1];
			for (i = n-1; i >= 0; i--) {
				A[C[B[i] / p % k]-1] = B[i];
				C[B[i] / p % k]--;
			}
		} else {
			// consider A as the intermediate input array
			for (i = 0; i < n; i++)
				C[A[i] / p % k]++;
			for (i = 1; i < k; i++)
				C[i] = C[i] + C[i-1];
			for (i = n-1; i >= 0; i--) {
				B[C[A[i] / p % k]-1] = A[i];
				C[A[i] / p % k]--;
			}
		}
	}

	if (d%2)
		for (i = 0; i < n; i++)
			cout << B[i] << " ";
	else
		for (i = 0; i < n; i++)
			cout << A[i] << " ";
	cout << endl;
	return 0;
}
