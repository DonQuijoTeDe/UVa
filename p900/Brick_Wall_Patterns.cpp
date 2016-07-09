#include <iostream>
using namespace std;

int main() {
	/* Observe that
	   n = 1, a1 = 1
	   n = 2, a2 = 2
	   n = 3, a3 = 3
	   n = 4, a4 = 5
	   n = 5, a5 = 8 */

	int length;

	int DP[51];
	DP[1] = 1;
	DP[2] = 2;

	for (int i = 3; i < 51; i++)
		DP[i] = DP[i - 1] + DP[i - 2];

	while (cin >> length && length) {

		cout << DP[length] << "\n";

	}

	return 0;
}