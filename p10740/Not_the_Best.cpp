#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* For adjList */
struct Pair {
	int to, w;
	Pair(){}
	Pair(int first, int second) :to(first), w(second){}
};

/* For priority queue */
struct Node {
	int pos, dis;
	Node(){}
	Node(int first, int second) :pos(first), dis(second){}
	bool operator< (const Node& a) const { return a.dis < dis; }
};

int main() {
	int n, m, src, des, k, u, v, l,
		i;

	while (cin >> n >> m && n + m) {
		cin >> src >> des >> k;

		/* Dynamic allocation */
		vector<Pair> *adjList = new vector<Pair>[n + 1];
		int** Dis = new int*[10 + 1];
		int* Visited = new int[n + 1];

		/* Initialize */
		for (i = 0; i <= 10; i++) {
			Dis[i] = new int[n + 1];
			fill(Dis[i], Dis[i] + n + 1, (int)1e9);
		}
		for (i = 0; i <= n; i++) {
			adjList[i].clear();
			Visited[i] = 0;
		}

		/* Store input */
		while (m--) {
			cin >> u >> v >> l;
			adjList[u].push_back({ v, l });
		}

		/* --- Start --- Dijkstra */
		priority_queue<Node> PQ;
		PQ.push(Node(src, 0));
		Dis[0][src] = 0;

		while (!PQ.empty()) {
			Node current = PQ.top();
			PQ.pop();
			if (Visited[current.pos] > k - 1) continue;
			
			/*cout << "Dis[" << Visited[current.pos] << "][" << current.pos << "] = "
				<< current.dis << "\n";*/

			Dis[Visited[current.pos]][current.pos] = current.dis;
			Visited[current.pos]++;
			
			for (i = 0; i < (int)adjList[current.pos].size(); i++) {
				Node next;
				next.pos = adjList[current.pos][i].to;
				next.dis = current.dis + adjList[current.pos][i].w;

				/* if (current.dis + adjList[current.pos][i].w < next.dis)
				 * 1. Do not check the above statement in relaxation
				 * 2. Since we do not know the node is in which stages.
				 * 3. That is, we may override Dis[2][2] by Dis[2][2]
				 *    with the same distance.
				 * 4. Also, this is the reason why I choose Dijkstra
				 *    instead of SPFA */

				PQ.push(next);
			}
		}
		/* --- End --- Dijkstra */

		/* Output */
		if (Dis[k - 1][des] != 1e9)
			cout << Dis[k - 1][des] << "\n";
		else
			cout << "-1\n";

		/* Release allocation */
		for (i = 0; i <= 10; i++)
			delete[] Dis[i];
		delete[] adjList;
		delete[] Dis;
		delete[] Visited;
		
	}

	return 0;
}