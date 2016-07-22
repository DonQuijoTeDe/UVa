#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Road{
	int u, v, w;
	Road(){};
	Road(int first, int second, int third):u(first),v(second),w(third){}
};

int Find(int);
void Union(int, int);
void Init(int);
int Kruskal(int, int);
bool Cmp(Road, Road);

vector<Road> roads;
vector<int> parent;

int main(){
	// Max Spanning Tree Problem
	// Run time : 0.18s

	int N, V, E,
		i, Case = 1;

	cin >> N;
	while (N--){
		cin >> V >> E;

		roads.clear();
		roads.reserve(E);
		Road temp;
		for (i = 0; i < E; i++){
			cin >> temp.u >> temp.v >> temp.w;
			roads.push_back(temp);
		}

		parent.clear();
		parent.resize(V);
		Init(V);

		sort(roads.begin(), roads.end(), Cmp); // we want to sort the weight in decreasing order
                                               // so, if Cmp return false means the former operand
                                               // is smaller than the later one and we need to swap it

		cout << "Case #" << Case << ": " << Kruskal(V, E) << "\n";
		Case++;
	}

	return 0;
}

void Init(int n){
	for (int i = 0; i < n; i++){
		parent[i] = i;
	}
}

int Find(int n){
	return n == parent[n] ? n : parent[n] = Find(parent[n]);
}

void Union(int a, int b){
	parent[Find(a)] = Find(b);
}

bool Cmp(Road a, Road b){
	return a.w > b.w;
}

int Kruskal(int V, int E){
	int answer = 0;
	for (int i = 0, j = 0; i < E && j < V - 1; i++){
		while (Find(roads[i].u) == Find(roads[i].v)){ // If it will produce a cycle then discard it
			                                          // until it won't produce a cycle
			i++;
		}

		Union(roads[i].u, roads[i].v);
		j++;
		if (j == V - 1){
			answer = roads[i].w;
		}
	}

	return answer;
}