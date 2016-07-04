#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Pair {
	int to;
	Pair(int first) : to(first) {}
};

int main() {
	int N, S,
		u, v,
		i,
		current, maxIndex, next,
		Case = 0;

	while (cin >> N && N) {
		cin >> S;
		Case++;

		/* Dynamic allocation */
		vector<Pair> *adjList = new vector<Pair>[N + 1];
		int* dis = new int[N+1];
		bool* inQueue = new bool[N+1];
		for (i = 1; i < N + 1; i++) {
			adjList[i].clear();
			dis[i] = 0;
			inQueue[i] = false;
		}

		while (cin >> u >> v && u + v)
			adjList[u].push_back({ v });

		/* --- Start --- Shortest Path Faster Algorithm */

		queue<int> q;
		q.push(S);
		while (!q.empty()) {
			current = q.front();
			q.pop();
			inQueue[current] = false;
			for (i = 0; i < (int)adjList[current].size(); i++) {
				next = adjList[current][i].to;
				if (dis[current] + 1 > dis[next]) {
					dis[next] = dis[current] + 1;
					if (!inQueue[next]) {
						q.push(next);
						inQueue[next] = true;
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
		delete[] adjList;
		delete[] dis;
		delete[] inQueue;
	}

	return 0;
}
