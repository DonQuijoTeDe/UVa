#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct Pair {
	int to, w;
	Pair(int first, int second) : to(first), w(second){}
};

struct Road {
	int v1, v2, speed;
	Road() : v1(-1), v2(-1), speed(0){}
	Road(int u, int v, int sp) : v1(u), v2(v), speed(sp){}
};

bool Cmp(Pair, Pair);
void Trace(int [], string [], int, int);

int main() {
	string A, B, src, des;
	int R, V, i, j, isArrived;
	bool line = true; // For its presentation format

	while (cin >> R) {
		isArrived = false;

		if (line)
			line = false;
		else
			cout << "\n";

		map<string, int> Id; /* Map : city(A) to index(0)
							  *       city(B) to index(1) */

		/* Due to runtime error on UVa online judge,
		   I can't allocate memories dynamically

		Dynamic allocation :
		int R1 = R + 10;
		vector<Pair> *adjList = new vector<Pair>[R1];
		bool** isVisited = new bool*[R1];
		int* parent = new int[R1];
		string* name = new string[R1];
		for (i = 0; i < R; i++)
			isVisited[i] = new bool[R1];

		Initialize :
		for (i = 0; i < R; i++) {
			adjList[i].clear();
			name[i] = "";
			parent[i] = i;
			for (j = 0; j < R; j++)
				isVisited[i][j] = false;
		}
		*/
		
		/* Static allocation */
		vector<Pair> adjList[500]; // At most 500 different cities
		bool isVisited[500][500];
		int parent[500];

		string name[500]; /* Map : use index(0) to find city(A)
						   *           index(1) to find city(B) */

		memset(isVisited, false, sizeof(isVisited));
		memset(parent, -1, sizeof(parent));
		memset(name, 0, sizeof(name));
		for (i = 0; i < 500; i++)
			adjList[i].clear();

		/* Store Input and Construct Map */
		for (i = 0; i < R; i++) {
			cin >> A >> B >> V;
			if (Id.find(A) == Id.end()) { // if map doesn't contain A
				Id.insert(make_pair(A, Id.size()));
				//cout << Id[A] << " ";
			}
			if (Id.find(B) == Id.end()) { // if map doesn't contain B
				Id.insert(make_pair(B, Id.size()));
				//cout << Id[B] << "\n";
			}

			adjList[Id[A]].push_back({ Id[B], V }); // Each city could have more than one edge
			adjList[Id[B]].push_back({ Id[A], V });
		}

		cin >> src >> des;

		queue<Road> q;

		/* Check source and destination are invalid or not */
		if (Id.find(src) != Id.end() && Id.find(des) != Id.end()) {

			for (i = 0; i < 500; i++)
				/* If there is more than one route, print that where
				 * the cities appear first in the input. So we need to
				 * sort it in input order */
				sort(adjList[i].begin(), adjList[i].end(), Cmp);

			Road road(Id[src], Id[src], 0); //source
			q.push(road);
		}

		/* --- Start --- BFS */
		while (!isArrived && !q.empty()) {
			Road current = q.front();
			q.pop();
			int v1 = current.v1;
			int v2 = current.v2;
			int speed = current.speed;

			for (i = 0; i < (int)adjList[v2].size(); i++) {
				int next_v2 = adjList[v2][i].to;
				if (adjList[v2][i].w >= speed && !isVisited[v2][next_v2]) {

					/* Be careful, we need to record two vertices.
					 * The source has two vertices and each vertice 
					 * points to itself */
					parent[next_v2] = v2; 
					parent[v2] = v1;
					isVisited[next_v2][v2] = isVisited[v2][next_v2] = true;
					
					Road next(v2, next_v2, adjList[v2][i].w);
					q.push(next);

					if (next_v2 == Id[des]) {
						isArrived = true;
						break;
					}
				}
			}
		}
		/* --- End --- BFS */

		/* Output */
		if (!isArrived && q.empty())
			cout << "No valid route.";
		else {
			for (map<string, int>::iterator it = Id.begin(); it != Id.end(); it++) {
				name[it->second] = it->first;
			}
			Trace(parent, name, Id[src], Id[des]);
		}
		cout << "\n";

		/*Release allocation
		for (i = 0; i < R; i++)
			delete[] isVisited[i];
		delete[] adjList;
		delete[] isVisited;
		delete[] parent;
		delete[] name;*/
	}

	return 0;
}

void Trace(int p[], string n[], int src, int des) {
	if (des == src) 
		cout << n[des];
	else {
		Trace(p, n, src, p[des]);
		cout << " " << n[des];
	}
}

bool Cmp(Pair a, Pair b) {
	return a.to < b.to;
}