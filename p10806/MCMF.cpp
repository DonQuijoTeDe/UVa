#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

#define INF 99999999
#define MAXN 205
vector<int> edge[MAXN];
int cap[MAXN][MAXN], flow[MAXN][MAXN], cost[MAXN][MAXN];
int pre[MAXN], dis[MAXN];
bool used[MAXN][MAXN];

void Initial(int N);
void MCMF(int S, int T);
bool SPFA(int S, int T);
void UpdateFlow(int S, int T, int bottleneck);

int main() {
	int N, M;
	while (cin >> N && N) {
		cin >> M;

		/* Initialize all arrays */
		Initial(N);

		/* Store Input Info */
		int u, v, t;
		for (int i = 0; i < M; i++) {
			cin >> u >> v >> t;
			cap[u][v] = cap[v][u] = 1;
			cost[u][v] = cost[v][u] = t;
			edge[u].push_back(v);
			edge[v].push_back(u);
		}

		/* Min Cost Max Flow */
		MCMF(N,1);

	}
}

void Initial(int N) {
	for (int i = 1; i <= N; i++) edge[i].clear();
	memset(cap, 0, sizeof(cap));
	memset(flow, 0, sizeof(flow));
	memset(cost, 0, sizeof(cost));
	memset(used, 0, sizeof(used));
}

void MCMF(int S, int T) {
	int min_cost = 0;
	int max_flow = 0;

	/* To check if there are two paths starting from S to T */

	/* Since the capacity is 1, if we can find two paths starting 
	 * from S to T which means we find the way the one in prison 
	 * can escape from the jail to train station without taking the
	 * repeated edges which have taken by his friend already
	 */

	/* SPFA means Shortest Path Faster Algorithm */
	while (SPFA(S, T)) {

		/* If we find a shortest path from S to T 
		 * we need to update the current info
		 */
		UpdateFlow(S, T, 1);
		min_cost += dis[T];
		max_flow++;
		if (max_flow >= 2) break;
	}
	if (max_flow < 2) cout << "Back to jail\n";
	else cout << min_cost << "\n";
}

/* To see how SPFA algorithm works, try following links :
 * http://stackoverflow.com/questions/7710995/shortest-paths-faster-spfa-algorithm
 * http://wcipeg.com/wiki/Shortest_Path_Faster_Algorithm
 */
bool SPFA(int S, int T) {
	fill(begin(dis), end(dis), INF);
	queue<int> Q;
	bool inQueue[MAXN] = { 0 };

	dis[S] = 0;
	Q.push(S);
	inQueue[S] = true;

	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		inQueue[cur] = false;

		/* For each edge connected to cur, consider two situations
		 * 1. negative flow (the dis will become smaller)
		 * 2. positive flow (the dis will become larger)
		 */
		for (int nxt : edge[cur]) {
			if (flow[nxt][cur] > 0 && dis[cur] + (-cost[nxt][cur]) < dis[nxt]) {
				dis[nxt] = dis[cur] + (-cost[nxt][cur]);
				pre[nxt] = cur;
				if (!inQueue[nxt]) {
					inQueue[nxt] = true;
					Q.push(nxt);
				}
			}
			else if (!used[cur][nxt] && cap[cur][nxt] > flow[cur][nxt] && dis[cur] + cost[cur][nxt] < dis[nxt]) {
				dis[nxt] = dis[cur] + cost[cur][nxt];
				pre[nxt] = cur;
				if (!inQueue[nxt]) {
					inQueue[nxt] = true;
					Q.push(nxt);
				}
			}
		}
	}
	return dis[T] != INF;
}

void UpdateFlow(int S, int T, int bottleneck) {
	for (int u = T; u != S; u = pre[u]) {
		flow[pre[u]][u] += bottleneck;
		flow[u][pre[u]] -= bottleneck;
		used[pre[u]][u] = used[u][pre[u]] = true;
	}
}