#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	// Run time : 0.00s

	string src, des;
	int digit, i, cur, nex;

	vector<int> adjList[26];
	map<char, int> Id; // I use map to build a relationship between character and index
	int inDegree[26];
	bool isUsed[26];

	// Initialize
	for (i = 0; i < 26; i++)
		adjList[i].clear();
	Id.clear();
	memset(inDegree, 0, sizeof(inDegree));
	memset(isUsed, false, sizeof(isUsed));
	
	// Build graph
	cin >> src;
	while (cin >> des && des != "#") {
		digit = src.length() > des.length() ? des.length() : src.length();
		for (i = 0; i < digit; i++) {
			if (src[i] == des[i]) {
				continue;
			}
			else {
				Id.insert(make_pair(src[i], Id.size()));
				Id.insert(make_pair(des[i], Id.size()));

				// If the relation X < Y hasn't been stored yet
				vector<int>::iterator it = find(adjList[Id[src[i]]].begin(), adjList[Id[src[i]]].end(), Id[des[i]]);
				if (it == adjList[Id[src[i]]].end()) {
					adjList[Id[src[i]]].push_back(Id[des[i]]);
					inDegree[Id[des[i]]]++;
					isUsed[Id[src[i]]] = isUsed[Id[des[i]]] = true;
				}
				break;
			}
		}
		src = des;
	}

	char name[26];
	for (map<char, int>::iterator it = Id.begin(); it != Id.end(); it++) {
		name[it->second] = it->first;
	}

	// Find the source point
	queue<int> q;
	for (i = 0; i < 26; i++) {
		if (isUsed[i] && inDegree[i] == 0) {
			q.push(i);
			break;
		}
	}

	// Topological sort
	while (!q.empty()) {
		cur = q.front();
		q.pop();

		for (i = 0; i < adjList[cur].size(); i++) {
			nex = adjList[cur][i];
			inDegree[nex]--;
			if (inDegree[nex] == 0) {
				q.push(nex);
			}
		}

		cout << name[cur];
	}

	cout << "\n"; // Get WA once !

	return 0;
}