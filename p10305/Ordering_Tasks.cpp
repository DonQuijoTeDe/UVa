#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int m, n, src, des, cur, nex,
		i;

	while (cin >> m >> n && m + n) {

		int* inDegree = new int[m + 1]; // Store in-degree of each node
		vector<int>* adjList = new vector<int>[m + 1]; // Store edge info

		// Initialize
		for (i = 1; i <= m; i++) {
			inDegree[i] = 0;
			adjList[i].clear();
		}
		
		vector<int>::iterator it; // Use iterator to find if this edge is already stored
		for (i = 0; i < n; i++) {
			cin >> src >> des;

			it = find(adjList[src].begin(), adjList[src].end(), des);
			if (it == adjList[src].end()) {
				adjList[src].push_back(des);
				inDegree[des]++;
			}
		}
		
		// Each node that has a 0 in-degree should be considered first
		queue<int> q;
		for (i = 1; i <= m; i++)
			if (inDegree[i] == 0)
				q.push(i);

		while (!q.empty()) {
			cur = q.front();
			q.pop();

			for (i = 0; i < (int)adjList[cur].size(); i++) {
				nex = adjList[cur][i];
				inDegree[nex]--;
				if (inDegree[nex] == 0)
					q.push(nex);
			}

			cout << cur << " ";
		}

		cout << "\n";

		delete[] inDegree;
		delete[] adjList;
	}

	return 0;
}