#include <iostream>
#include <queue>
using namespace std;

int main() {
	int c, n, m, x, y, t,
		i, j, current;
	bool isCyclic;

	cin >> c;
	while (c--) {
		cin >> n >> m;

		isCyclic = false;

		/* Dynamic allocation */
		int* dis = new int[n];
		bool* inQueue = new bool[n];
		int* p = new int[n];
		int** w = new int*[n];
		for (i = 0; i < n; i++)
			w[i] = new int[n];

		/* Initialize */
		for (i = 0; i < n; i++) {
			dis[i] = 1e9;
			inQueue[i] = false;
			p[i] = 0;
			for (j = 0; j < n; j++)
				w[i][j] = 1e9;
		}

		/* Store Input */
		for (i = 0; i < m; i++) {
			cin >> x >> y >> t;
			w[x][y] = t;
		}

		/* --- Start --- SPFA */
		queue<int> q;
		q.push(0);
		//inQueue[0] = true;
		dis[0] = 0;

		while (!isCyclic && !q.empty()) {
			current = q.front();
			q.pop();
			inQueue[current] = false;

			for (i = 0; i < n; i++) {
				if (w[current][i] != 1e9 && dis[current] + w[current][i] < dis[i]) {
					dis[i] = dis[current] + w[current][i];
					p[i] = p[current] + 1;
					if (p[i] >= n) {
						isCyclic = true;
						break;
					}
					if (!inQueue[i]) {
						q.push(i);
						inQueue[i] = true;
					}
				}
			}
		}
		/* --- End --- SPFA */

		/* Output */
		if (isCyclic)
			cout << "possible\n";
		else
			cout << "not possible\n";

		/* Release allocation */
		for (i = 0; i < n; i++)
			delete[] w[i];
		delete[] dis;
		delete[] inQueue;
		delete[] p;
		delete[] w;
	}
}
