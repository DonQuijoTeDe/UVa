#include <iostream>
#include <sstream>
#include <string.h>
#include <queue>
using namespace std;

int main() {
	int n, des, floor, current, next,
		i, j, k1, k2;
	string str = "";

	int temp[100];
	int W[100][100];
	int Time[100];
	int T[6];
	int inQueue[100];

	while (cin >> n >> des && (n + des)) {

		/* Initialize */
		memset(T, 0, sizeof(T));
		for (i = 0; i < 100; i++) {
			Time[i] = (int)1e9;
			inQueue[i] = false;
			temp[i] = 0;
			for (j = 0; j < 100; j++)
				W[i][j] = (int)1e9;
		}

		/* 1. Store Input
		 * 2. Calculate the minimum time from floor k1 to k2 
		 *    in the same elevator first */
		for (i = 1; i <= n; i++)
			cin >> T[i];

		cin.ignore();

		for (i = 1; i <= n; i++) {
			getline(cin, str);
			stringstream ss(str);
			j = 0;
			while (ss >> floor) {
				temp[j] = floor;
				j++;
			}
			for (k1 = 0; k1 < j - 1; k1++) {
				for (k2 = k1 + 1; k2 < j; k2++)
					if (T[i] * (temp[k2] - temp[k1]) < W[temp[k1]][temp[k2]]) {
						/*cout << "(" << temp[k1] << " " << temp[k2] << "):" 
							 << T[i] * (temp[k2] - temp[k1]) << " ";*/
						W[temp[k1]][temp[k2]] = W[temp[k2]][temp[k1]] = T[i] * (temp[k2] - temp[k1]);
					}
			}
		}

		/* --- Start --- SPFA */
		queue<int> q;
		q.push(0);
		//inQueue[0] = true;
		Time[0] = 0;

		while (!q.empty()) {
			current = q.front();
			q.pop();
			inQueue[current] = false;

			for (next = 0; next < 100; next++) {
				if (Time[current] + W[current][next] + 60 < Time[next]) {
					Time[next] = Time[current] + W[current][next] + 60;
					if (!inQueue[next]) {
						q.push(next);
						inQueue[next] = true;
					}
				}
			}
		}
		/* --- End --- SPFA */

		/* Output */
		if (des == 0)
			cout << 0;
		else if (Time[des] != 1e9)
			cout << Time[des] - 60;
		else
			cout << "IMPOSSIBLE";

		cout << "\n";
	}

	return 0;
}

