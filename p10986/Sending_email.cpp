#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Pair {
	int to, w;
	Pair(int first, int second) : to(first), w(second){}
};

int main() {
	int Case, n, m, src, des,
		from, to, weight, current, next,
		i, j;
	cin >> Case;

	for (i = 1; i <= Case; i++) {
		cin >> n >> m >> src >> des;

		/* Dynamic allocation */
		vector<Pair> *adjList = new vector<Pair>[n];
		int* Dis = new int[n];
		bool* inQueue = new bool[n];

		/* Initialize */
		for (j = 0; j < n; j++) {
			adjList[j].clear();
			Dis[j] = (int)1e9;
			inQueue[j] = false;
		}

		/* Store input */
		while (m--) {
			cin >> from >> to >> weight;
			adjList[from].push_back({ to, weight });
			adjList[to].push_back({ from, weight }); // It is bidirectional !
		}

		/* SPFA */
		queue<int> q;
		q.push(src);
		inQueue[src] = true;
		Dis[src] = 0;

		while (!q.empty()) {
			current = q.front();
			q.pop();
			inQueue[current] = false;

			for (j = 0; j < (int)adjList[current].size(); j++) {
				next = adjList[current][j].to;
				weight = adjList[current][j].w;
				if (Dis[current] + weight < Dis[next]) {
					Dis[next] = Dis[current] + weight;
					if (!inQueue[next]) {
						q.push(next);
						inQueue[next] = true;
					}
				}
			}
		}

		/* Output */
		cout << "Case #" << i << ": ";
		if (Dis[des] != 1e9)
			cout << Dis[des];
		else
			cout << "unreachable";
		cout << "\n";

		delete[] adjList;
		delete[] Dis;
		delete[] inQueue;
	}

	return 0;
}