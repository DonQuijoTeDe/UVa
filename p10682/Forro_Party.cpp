#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct Pair{
	int to, w;
	Pair(){};
	Pair(int first, int second) : to(first), w(second){}
};

struct Road{
	int v1, v2, speed;
	Road() : v1(-1), v2(-1), speed(0){}
	Road(int u, int v, int sp) : v1(u), v2(v), speed(sp){}
};

bool Cmp(Pair, Pair);
void Trace(int, int);
void Init();
void ConstructMap(int);
bool BFS(int, int);

vector<Pair> adjList[500]; // At most 500 different cities
map<string, int> Id; // Map: city(A) to index(0), city(B) to index(1)
string name[500]; // Map: use index(0) to find city(A), index(1) to find city(B)
bool isVisited[500][500];
int parent[500];

int main() {
  // Reference: http://bruce30262.pixnet.net/blog/post/96702131-%5Bc-c%2B%2B%5D-uva-10682----forr

	string src, des;
	int R, i, j;
	bool line = true; // Presentation format

	while (cin >> R){
		if (line)
			line = false;
		else
			cout << "\n";

		Init();
		ConstructMap(R);

		cin >> src >> des;
		if (Id.find(src) == Id.end() || Id.find(des) == Id.end()){ // Check if source and destination are invalid
			cout << "No valid route.";
		}
		else{
			for (i = 0; i < 500; i++)
				/* If there is more than one solution route, print that where
				 * the cities appear first in the input. So we need to sort it
				 * in input order */
				sort(adjList[i].begin(), adjList[i].end(), Cmp);

			if (BFS(Id[src], Id[des])){
				for (map<string, int>::iterator it = Id.begin(); it != Id.end(); it++) {
					name[it->second] = it->first;
				}

				Trace(Id[src], Id[des]);
			}
			else{
				cout << "No valid route.";
			}
		}
		cout << "\n";
	}

	return 0;
}

void Trace(int src, int des) {
	if (des == src)
		cout << name[des];
	else {
		Trace(src, parent[des]);
		cout << " " << name[des];
	}
}

bool Cmp(Pair a, Pair b) {
	return a.to < b.to;
}

void Init(){
	for (int i = 0; i < 500; i++){
		adjList[i].clear();
	}
	Id.clear();
	memset(isVisited, false, sizeof(isVisited));
	memset(parent, -1, sizeof(parent));
	memset(name, 0, sizeof(name));
}

void ConstructMap(int R){
	string A, B;
	int V;

	for (int i = 0; i < R; i++){
		cin >> A >> B >> V;
		if (Id.find(A) == Id.end()){ // if map doesn't contain A
			Id.insert(make_pair(A, Id.size()));
			//cout << Id[A] << " ";
		}
		if (Id.find(B) == Id.end()){ // if map doesn't contain B
			Id.insert(make_pair(B, Id.size()));
			//cout << Id[B] << "\n";
		}

		adjList[Id[A]].push_back({ Id[B], V }); // Each city could have more than one edge
		adjList[Id[B]].push_back({ Id[A], V });
	}
}

bool BFS(int src, int des){
	queue<Road> q;
	Road road(src, src, 0); //source
	q.push(road);
	while (!q.empty()){
		Road current = q.front();
		q.pop();
		int v1 = current.v1;
		int v2 = current.v2;
		int speed = current.speed;

		for (int i = 0; i < (int)adjList[v2].size(); i++){
			int next_v2 = adjList[v2][i].to;
			if (adjList[v2][i].w >= speed && !isVisited[v2][next_v2]){

				/* Be careful, we need to record two vertices.
				 * The source has two vertices and each vertice
				 * points to itself */
				parent[next_v2] = v2;
				parent[v2] = v1;
				isVisited[next_v2][v2] = isVisited[v2][next_v2] = true;

				Road next(v2, next_v2, adjList[v2][i].w);
				q.push(next);

				if (next_v2 == des){
					return true;
				}
			}
		}
	}

	return false;
}
