#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
using namespace std;

int main() {
	int i, n;
	double k;
	cout << "Number of Elements: ";
	cin >> n;
	vector<double> A;
	vector<list<double>> B(n);
	cout << "Elements: ";
	for (i = 0; i < n; i++) {
		cin >> k;
		B[(n*k)/1].push_back(k);
	}
	for (i = 0; i < n; i++)
		B[i].sort();
	i = 0;
	while (i < n) {
		if (!B[i].size()) {
			i++;
			continue;
		}
		A.push_back(B[i].front());
		B[i].pop_front();
	}
	cout << setprecision(15);
	for (i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
	return 0;
}
