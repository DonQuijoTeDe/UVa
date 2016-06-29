#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	int N, S,
		u, v,
		i, j,
		current, maxIndex,
		Case = 0;

	while (cin >> N && N) {
		cin >> S;
		Case++;

		/* Dynamic allocation */
		bool** edge = new bool*[N+1];
		int* dis = new int[N+1];
		bool* inQueue = new bool[N+1];
		for (i = 1; i < N + 1; i++) {
			edge[i] = new bool[N + 1];
			dis[i] = 0;
			inQueue[i] = false;
		}

		for (i = 1; i < N + 1; i++)
			for (j = 1; j < N + 1; j++)
				edge[i][j] = false;

		while (cin >> u >> v && u + v)
			edge[u][v] = true;


		/* --- Start --- Shortest Path Faster Algorithm */

		queue<int> q;
		q.push(S);
		while (!q.empty()) {
			current = q.front();
			q.pop();
			inQueue[current] = false;
			for (i = 1; i < N + 1; i++) {
				if (edge[current][i] && (dis[current] + 1 > dis[i])) {
					dis[i] = dis[current] + 1;
					if (!inQueue[i]) {
						q.push(i);
						inQueue[i] = true;
					}
				}
			}
		}

		/* --- End --- Shortest Path Faster Algorithm */

		/* Find the longest paths */
		maxIndex = 1;
		for (i = 2; i < N + 1; i++) {
			if (dis[i] > dis[maxIndex])
				maxIndex = i;
		}

		cout << "Case " << Case << ": The longest path from " << S
			 << " has length " << dis[maxIndex] << ", finishing at " << maxIndex << ".\n\n";

		/* Release allocation */
		for (i = 1; i < N + 1; i++)
			delete[] edge[i];
		delete[] edge;
		delete[] dis;
		delete[] inQueue;
	}

	return 0;
}
