#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
	int price, favour;
};

int main() {
	// DP Problem
	// Run time : 0.12s

	int budget, n, total, output,
		i, j;

	while (cin >> budget >> n) {

		Item* item = new Item[n];
		for (i = 0; i < n; i++)
			cin >> item[i].price >> item[i].favour;

		// Check refund
		total = 0;
		if (budget > 1800)
			total = budget + 200;
		else
			total = budget;

		int** DP = new int*[n + 1];
		for (i = 0; i <= n; i++) {
			DP[i] = new int[total + 1];
			fill(DP[i], DP[i] + total + 1, 0);
		}

		/*
		The twist in this problem lies in:
		Consider the following case
		1801 3
		2000 3
		1900 1
		101 1

		First: the best answer is 2($1900 + $101) not 3($2000)
		because we can not get the refund($200) until we
		expensed more than $2000

		Second: be careful that your DP table should store the "exact"
		value of each input price
		i.e.,
		DP[1][2000] = 3
		DP[2][1900] = 1
		DP[2][2000] = 3 (we do not override DP[2][1900] with DP[2][2000])
		DP[3][101] = 1
		DP[3][1900] = 1
		DP[3][2000] = 3
		DP[3][2001] = DP[2][2001 - 101] + 1 = 2

		*/
		for (i = 0; i < n; i++) { 
			for (j = 0; j <= total; j++) {
				if (j >= item[i].price && (DP[i][j - item[i].price] > 0 || j == item[i].price)) {
					DP[i + 1][j] = max(DP[i][j], DP[i][j - item[i].price] + item[i].favour);
					//cout << "DP[" << i + 1 << "][" << j << "]:"
						//<< DP[i + 1][j] << "\n";
				}
				else {
					DP[i + 1][j] = DP[i][j];
				}
			}
		}

		// Output
		output = 0;
		if (budget > 1800 && budget < 2001) {
			for (i = 1; i <= n; i++) {
				for (j = 0; j <= budget; j++) {
					output = max(output, DP[i][j]);
				}
				for (j = 2001; j <= total; j++) {
					output = max(output, DP[i][j]);
				}
			}
		}
		else {
			for (i = 1; i <= n; i++) {
				for (j = 0; j <= total; j++) {
					output = max(output, DP[i][j]);
				}
			}
		}
		cout << output << "\n";

		for (i = 0; i <= n; i++)
			delete[] DP[i];
		delete[] DP;
		delete[] item;

	}

	return 0;
}