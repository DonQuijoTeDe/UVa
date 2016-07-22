#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	// DP Problem
	// Run time : 0.14s
	// Reference : http://naivered.github.io/2016/04/04/Problem_Solving/UVa/UVa-10465-Homer-Simpson/
	// We can view this problem as solving the equation: 
	// mx + ny = t and find the minimum difference to t

	int m, n, t,
		i, j;

	while (cin >> m >> n >> t) {

		int item[2] = { m, n };
		int* DP = new int[t + 1];
		int* Beer = new int[t + 1];

		fill(Beer, Beer + t + 1, -1);
		fill(DP, DP + t + 1, 0);
		Beer[0] = 0;
		for (i = 0; i < 2; i++) { // Try two kinds of burger
			for (j = item[i]; j <= t; j++) { // Try all kinds of minute
				if (Beer[j - item[i]] != -1) {
					if (DP[j - item[i]] + 1 > DP[j]) {
						DP[j] = DP[j - item[i]] + 1;
						Beer[j] = 0;
						//cout << "DP[" << j << "]:" << DP[j]
							//<< " , DP[" << j - item[i] << "]:" << DP[j - item[i]] << " +1 "
							//<< "Beer[" << j << "]:" << Beer[j] << "\n";
					}
				}
			}
		}

		for (i = t; i >= 0; i--) {
			if (Beer[i] == 0) {
				cout << DP[i];
				break;
			}
		}
		if (t - i != 0)
			cout << " " << t - i;
		cout << "\n";

		delete[] DP;
		delete[] Beer;

	}

	return 0;
}