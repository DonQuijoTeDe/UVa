#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 3000005

long long dp[MAXN] = {};
int used[MAXN] = {}, ob[MAXN] = {};

int main() {
	memset(dp, 0, sizeof(dp));
	memset(ob, 0, sizeof(ob));
	memset(used, 0, sizeof(used));
	int DIM, R, dim[16], row[16], v[16],
	    testcase = 0, cases = 0;

	while (cin >> DIM >> R && DIM+R) {
		for (int i = 0; i < DIM; i++) {
			cin >> dim[i];
			dim[i]++;
			/* since the input is the coordinate, in
			 * order to calculate it dimension , we need
			 * to add 1 to it */
		}
		testcase++;

		/* row major */
		row[DIM - 1] = 1;
		for (int i = DIM - 2; i >= 0; i--)
			row[i] = row[i + 1] * dim[i + 1];

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < DIM; j++)
				cin >> v[j];

			int x = 0;
			for (int j = 0; j < DIM; j++)
				x += v[j] * row[j];

			ob[x] = testcase;
		}
		/* when the starting point has an obstacle */
		if (ob[0] == testcase) {
			cout << "Case " << ++cases << ": 0\n";
			continue;
		}
		int dest = 0;
		for (int i = 0; i < DIM; i++)
			dest += (dim[i] - 1) * row[i];

		/* dynamic programming */
		queue<int> Q;
		Q.push(0), used[0] = testcase;
		dp[0] = 1;
		while (!Q.empty()) {
			int x = Q.front();
			Q.pop();
			long long ways = dp[x];

			for (int i = 0; i < DIM; i++)       /* use row major to calculate*/
				v[i] = x / row[i], x %= row[i]; /* our position right now */

			//cout << "(" << v[0] << "," << v[1] << ")  ";
			for (int i = 0; i < DIM; i++) {
				v[i]++;
				if (v[i] < dim[i]) {
					x = 0;
					for (int j = 0; j < DIM; j++) {
						x += v[j] * row[j];
					}
					if (ob[x] != testcase) {
						if (used[x] != testcase)
							dp[x] = 0;

						dp[x] += ways;
						if (used[x] != testcase)
							Q.push(x), used[x] = testcase;
					}
					//cout << "dp[" << x << "]: " << dp[x] << " ";
				}
				v[i]--;
			}
			//cout << "\n";
		}
		if (used[dest] != testcase)
			dp[dest] = 0;

		cout << "Case " << ++cases << ": " << dp[dest] << "\n";
	}
	return 0;
}