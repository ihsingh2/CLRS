#include <iostream>
#include <vector>
using namespace std;

int main() {
	int i;
	unsigned int k, n;
	cout << "Number of Elements: ";
	cin >> n;
	cout << "Upper Bound: ";
	cin >> k;
	vector<unsigned int> A(n), B(n), C(k+1, 0);
	cout << "Elements: ";
	for (i = 0; i < n; i++) {
		cin >> A[i];
		C[A[i]]++;
	}
	for (i = 1; i <= k; i++)
		C[i] = C[i] + C[i-1];
	for (i = n-1; i >= 0; i--) {
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}
	for (i = 0; i < n; i++)
		cout << B[i] << " ";
	cout << endl;
	return 0;
}
