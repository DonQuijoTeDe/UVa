#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	long long DP[20][20],
		max_value,
		max_value1,
		max_value2;

	int i, j, k,
		n, value;

	while (cin >> n >> value) {
		memset(DP, -1, sizeof(DP));

		DP[n][1] = value;

		for (i = n; i >= 1; i--)
			for (j = 1; j <= n; j++) {
				if (i == n && j == 1) {
					//cout << "DP[" << i << "][" << j << "] = " << DP[i][j] << "\n";
					continue;
				}
				if (i >= j) {
					max_value1 = 0;
					for (k = i + 1; k <= n; k++)
						max_value1 = max(max_value1, DP[k][1] + DP[k][j]);

					max_value2 = 0;
					for (k = 1; k < j; k++)
						max_value2 = max(max_value2, DP[i][k] + DP[n][k]);

					DP[i][j] = max_value1 + max_value2;
					//cout << "DP[" << i << "][" << j << "] = " << DP[i][j] << "\n";

				} else {
					max_value = 0;
					for (k = i; k < j; k++)
						max_value = max(max_value, DP[i][k] + DP[k + 1][j]);

					DP[i][j] = max_value;
					//cout << "DP[" << i << "][" << j << "] = " << DP[i][j] << "\n";
				}
			}

		cout << DP[1][n] << "\n";
	}

	return 0;
}