#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Pair {
	int to, w;
	Pair(int first, int second) : to(first), w(second){}
};

int main() {
	int c, n, m, x, y, t,
		i, current, next, next_w;
	bool isCyclic;

	cin >> c;
	while (c--) {
		cin >> n >> m;

		isCyclic = false;

		/* Dynamic allocation */
		vector<Pair> *adjList = new vector<Pair>[n];
		int* dis = new int[n];
		bool* inQueue = new bool[n];
		int* r = new int[n];

		/* Initialize */
		for (i = 0; i < n; i++) {
			adjList[i].clear();
			dis[i] = (int)1e9;
			inQueue[i] = false;
			r[i] = 0;
		}
			
		/* Store Input */
		for (i = 0; i < m; i++) {
			cin >> x >> y >> t;
			adjList[x].push_back({ y, t });
		}

		/* --- Start --- SPFA */
		queue<int> q;
		q.push(0);
		dis[0] = 0;

		while (!isCyclic && !q.empty()) {
			current = q.front();
			q.pop();
			inQueue[current] = false;

			for (i = 0; i < (int)adjList[current].size(); i++) {
				next = adjList[current][i].to;
				next_w = adjList[current][i].w;
				if (dis[current] + next_w < dis[next]) {
					dis[next] = dis[current] + next_w;
					r[next] = r[current] + 1;
					if (r[next] >= n) {
						isCyclic = true;
						break;
					}
					if (!inQueue[next]) {
						q.push(next);
						inQueue[next] = true;
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
		delete[] adjList;
		delete[] dis;
		delete[] inQueue;
		delete[] r;
	}
}