#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
	vector<int> list;
	int energy, doorways;
};

int main() {
	int n, value, leave,
		next, current, isFinal, isCyclic,
		i, j, m, k;

	while (cin >> n && n != -1) {
		isFinal = false;
		isCyclic = false;

		/* Dynamic allocation */
		bool** transitive = new bool*[n + 1];
		Node* node = new Node[n + 1];
		int* dis = new int[n + 1];
		int* r = new int[n + 1];
		bool* inQueue = new bool[n + 1];
		for (i = 1; i <= n; i++)
			transitive[i] = new bool[n + 1];

		/* Initialize */
		for (i = 1; i <= n; i++) {
			dis[i] = -1e9;
			r[i] = 0;
			inQueue[i] = false;
			for (j = 1; j <= n; j++)
				transitive[i][j] = false;
		}

		/* Store Input */
		for (i = 1; i <= n; i++) {
			cin >> value >> leave;
			node[i].energy = value;
			node[i].doorways = leave;
			for (j = 0; j < node[i].doorways; j++) {
					cin >> next;
					node[i].list.push_back(next);
			}
		}

		/* --- Start --- BFS : To check if it is transitive */
		queue<int> Q;
		for (i = 1; i <= n; i++) {
			Q.push(i);
			while (!Q.empty()) {
				next = Q.front();
				Q.pop();

				if (transitive[i][next])
					continue;
				else
					transitive[i][next] = true;

				for (j = 0; j < node[next].doorways; j++)
					Q.push(node[next].list[j]);
			}
		}
		/* --- End --- BFS */

		/* --- Start --- SPFA */
		queue<int> q;
		q.push(1);
		dis[1] = 100;

		while (!q.empty()) {
			current = q.front();
			q.pop();
			inQueue[current] = false;

			/* Case 1 : Reaches the end */
			if (current == n) {
				isFinal = true;
				break;

			/* Case 2 : Has the cycle */
			} else if (r[current] >= n) {
				/* case 2-A : Can reach the end */
				if (transitive[current][n]) {
					isCyclic = true;
					break;

				/* case 2-B : Can't reach the end */
				} else
					dis[current] = 1e9;
				continue;
			}

			/* Update the energy after arriving next room */
			for (i = 0; i < node[current].doorways; i++) {
				m = node[current].list[i];
				k = dis[current] + node[current].energy;
				if (k > 0 && k > dis[m]) {
					dis[m] = k;
					r[m] = r[current] + 1;
					if (!inQueue[m]) {
						q.push(m);
						inQueue[m] = true;
					}
				}
			}
		}
		/* --- End --- SPFA */

		/* Output */
		if (isFinal || isCyclic)
			cout << "winnable\n";
		else if (dis[n] > 0)
			cout << "winnable\n";
		else
			cout << "hopeless\n";

		/* Release allocation */
		for (i = 1; i <= n; i++)
			delete[] transitive[i];
		delete[] node;
		delete[] transitive;
		delete[] dis;
		delete[] r;
		delete[] inQueue;

	}

	return 0;
}
