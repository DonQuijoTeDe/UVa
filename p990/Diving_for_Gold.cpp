#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
	int depth, value;
};

int main() {
	// DP Problem
	// Run time : 0.00s

	int time, parameter, n,
		i, j;
	bool first = false;

	while (cin >> time >> parameter) {
		cin >> n;

		Item* item = new Item[n];

		for (i = 0; i < n; i++) {
			cin >> item[i].depth;
			cin >> item[i].value;
		}

		int** dp = new int*[n + 1];
		for (i = 0; i <= n; i++) {
			dp[i] = new int[time + 1];
		}

		// Initialize
		fill(dp[0], dp[0] + time + 1, 0);

		for (i = 0; i < n; i++) { // Try every kind of treasure
			for (j = 0; j <= time; j++) { // Try every different time
				if (j - (item[i].depth) * 3 * parameter < 0) {
					dp[i + 1][j] = dp[i][j];
					/*cout << "dp[" << i + 1 << "][" << j << "]:" << dp[i][j] << "\n";*/
				}
				else {
					dp[i + 1][j] = max(dp[i][j], dp[i][j - (item[i].depth) * 3 * parameter] + item[i].value);
					/*cout << "dp[" << i + 1 << "][" << j << "]:" << " max{ "
						<< "dp[" << i << "][" << j << "]:" << dp[i][j]
						<< ", dp[" << i << "][" << j - (item[i].depth) * 3 * parameter << "]:" 
						<< dp[i][j - (item[i].depth) * 3 * parameter] << " + "
						<< "item[" << i << "].value:" << item[i].value << " }\n";*/
				}
			}
		}

		// Tracking
		vector<int> seq;
		for (i = n - 1, j = time; i >= 0; i--) {
			if (j - (item[i].depth) * 3 * parameter >= 0 && 
				dp[i + 1][j] == dp[i][j - (item[i].depth) * 3 * parameter] + item[i].value)
			{
				seq.push_back(i);
				j -= (item[i].depth) * 3 * parameter;
			}
		}

		// Get WA once :(
		if (first)
			cout << "\n";
		else
			first = true;

		// Output
		cout << dp[n][time] << "\n";
		cout << seq.size() << "\n";
		for (vector<int>::reverse_iterator it = seq.rbegin(); it != seq.rend(); it++) {
			cout << item[*it].depth << " " << item[*it].value << "\n";
		}

		for (i = 0; i <= n; i++)
			delete[] dp[i];
		delete[] dp;
		delete[] item;

	}

	return 0;
}