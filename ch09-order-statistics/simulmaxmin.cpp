#include <iostream>
#include <vector>
using namespace std;

int main() {
	int i, n, max, min, cmax, cmin;
	cout << "Enter the number of elements: ";
	cin >> n;
	vector<int> A;
	A.reserve(n);
	cout << "Enter the set of elements: ";
	for (i = 0; i < n; i++) cin >> A[i];

	if (n == 1) {
		cout << A[0] << endl;
		return 0;
	}

	if (n % 2) {
		min = A[0];
		max = A[0];
		i = 1;
	} else {
		if (A[0] > A[1]) {
			min = A[1];
			max = A[0];
		} else {
			min = A[0];
			max = A[1];
		}
		i = 2;
	}

	for (i; i < n; i = i+2)
	{
		if (A[i] > A[i+1]) {
			cmin = A[i+1];
			cmax = A[i];
		} else {
			cmin = A[i];
			cmax = A[i+1];
		}

		if (min > cmin) min = cmin;
		if (cmax > max) max = cmax;
	}

	cout << "Minimum: " << min << endl;
	cout << "Maximum: " << max << endl;
	return 0;
}
