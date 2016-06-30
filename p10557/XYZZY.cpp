#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;

struct Pair {
	int to, energy;
	Pair(int first, int second) : to(first), energy(second){}
};

int main() {
	int n, value, leave,
		next, current, isFinal, isCyclic, total,
		i, j;

	while (cin >> n && n != -1) {
		isFinal = false;
		isCyclic = false;
		
		/* Dynamic allocation */
		vector<Pair> *adjList = new vector<Pair>[n + 1];
		int* energy = new int[n + 1];
		int* r = new int[n + 1];
		bool* inQueue = new bool[n + 1];

		/* I'm still working here to carry out
		 * if there is a method that I don't have
		 * to declare this trasition table to make
		 * my code more efficient. Although I can
		 * allocate memories dynamically, I still
		 * need to initialize it in O(n^2) time. So
		 * I use memset to request a block of memory
		 * as quickly as possible */
		bool transitive[101][101];
		memset(transitive, false, sizeof(transitive));

		/* Initialize */
		for (i = 1; i <= n; i++) {
			energy[i] = (int)-1e9;
			r[i] = 0;
			inQueue[i] = false;
			adjList[i].clear();
		}
			
		/* Store Input */
		for (i = 1; i <= n; i++) {
			cin >> value >> leave;
			if (leave)
				for (j = 0; j < leave; j++) {
					cin >> next;
					adjList[i].push_back({ next, value });
				}
			/*else
				adjList[i].push_back({ -1, value});*/
		}

		/* --- Start --- BFS : To check if it is transitive
		 * That is, if 1 -> 2 and 2 -> 3 then 1 -> 3 */
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

				for (j = 0; j < (int)adjList[next].size(); j++)
					Q.push(adjList[next][j].to);
			}
		}
		/* --- End --- BFS */

		/* --- Start --- SPFA */
		queue<int> q;
		q.push(1);
		energy[1] = 100;

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
					energy[current] = (int)1e9;
				continue;
			}

			/* Update the energy after arriving next room */
			for (i = 0; i < (int)adjList[current].size(); i++) {
				next = adjList[current][i].to;
				total = energy[current] + adjList[current][i].energy;
				if (total > 0 && total > energy[next]) {
					energy[next] = total;
					r[next] = r[current] + 1;
					if (!inQueue[next]) {
						q.push(next);
						inQueue[next] = true;
					}
				}
			}
		}
		/* --- End --- SPFA */

		/* Output */
		if (isFinal || isCyclic)
			cout << "winnable\n";
		else if (energy[n] > 0)
			cout << "winnable\n";
		else
			cout << "hopeless\n";

		/* Release allocation */
		delete[] adjList;
		delete[] inQueue;
		delete[] r;
		delete[] energy;
	}

	return 0;
}