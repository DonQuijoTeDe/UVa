#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void copy(double a[][21], double b[][21], int n) {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			b[i][j] = a[i][j];
}

int main() {
	int index, N;
	bool find;
	while (cin >> N) {
		double best[21][21] = { 0 };
		double best_temp[21][21] = { 0 };
		double w[21][21] = { 0 };
		int path[21][21] = { 0 };

		/* Initialize */
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				path[i][j] = i;
				if (i == j)
					w[i][j] = 1.0;
				else
					cin >> w[i][j];
				best[i][j] = w[i][j];
			}
		}

		/* Floyd warshall algorithm 
		 * we can use 2-D array instead of
		 * 3-D array to make it faster 
		 * and do not waste any spaces */
		find = false;
		int s, i, j, k;
		for (s = 2; s <= N; s++) {
			copy(best, best_temp, N); /* We need to preserve the previous result in best_temp array */
			for (k = 1; k <= N; k++)
				for (i = 1; i <= N; i++)
					for (j = 1; j <= N; j++)
						if (best_temp[i][k] * w[k][j] > best[i][j]) {
							best[i][j] = best_temp[i][k] * w[k][j];
							path[i][j] = k;
						}

			/* After one step, we can check whether there is a
			 * valid solution or not */
			for (i = 1; i <= N; i++)
				if (best[i][i] > 1.01) {
					find = true;
					index = i;
					break;
				}
			if (find)
				break;
		}

		if (find == false)
			cout << "no arbitrage sequence exists";
		else {
			/* Print out the path 
			 * since we know how many times the result 
			 * needs ( we have already preserved it in
			 * variable s ) and now simply just uses it
			 * to trace back the path ) */
			vector<int> temp(s + 1);
			temp[s] = index;
			int predecessor = index;
			while (--s) {
				predecessor = path[index][predecessor];
				temp[s] = predecessor;
			}
			temp[s] = index;
			cout << temp[0];
			for (i = 1; i<temp.size(); i++)
				cout << " " << temp[i];
		}
		cout << "\n";
	}

	return 0;
}
