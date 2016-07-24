#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

struct Point{
	int x, y;
	Point(){};
};

struct Highway{
	int u, v;
	double len;
	Highway(){};
	Highway(int first, int second) :u(first), v(second){}
};

bool CmpHighway(Highway, Highway);
int Find(int);
void Union(int, int);
void Init(int);
void Kruskal(int, int);

vector<Highway> highways;
vector<int> boss;

int main(){
	// Min Spanning Tree Problem
	// Run time : 0.21s

	int Case, N, M, u, v,
		i, j;
	bool first = true;

	vector<Point> points;

	highways.reserve(375 * 749); // At most (750,2) edges, where 750 is the number of
	                             // points to choose from, and we choose 2 of them

	cin >> Case;
	while (Case--){
		if (first) 
			first = false;
		else
			cout << "\n";

		cin >> N;
		points.clear();
		points.reserve(N);
		Point tmp1;
		for (i = 0; i < N; i++){
			cin >> tmp1.x >> tmp1.y;
			points.push_back(tmp1);
		}

		// The distance between two points
		highways.clear();
		Highway tmp2;
		for (i = 0; i < N - 1; i++){ 
			for (j = i + 1; j < N; j++){
				tmp2.len = sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2));
				tmp2.u = i;
				tmp2.v = j;
				highways.push_back(tmp2);
			}
		}

		boss.clear();
		boss.resize(N);
		Init(N);

		cin >> M;
		for (i = 0; i < M; i++){
			cin >> u >> v;
			if (u > v){
				swap(u, v);
			}
			Union(u - 1, v - 1); // Key point: union the existed edges first
		}

		sort(highways.begin(), highways.end(), CmpHighway);

		Kruskal(highways.size(), N);
	}

	return 0;
}

bool CmpHighway(Highway a, Highway b){
	return a.len < b.len;
}

int Find(int n){
	return n == boss[n] ? n : boss[n] = Find(boss[n]);
}

void Init(int n){
	for (int i = 0; i < n; i++){
		boss[i] = i;
	}
}

void Union(int a, int b){
	boss[Find(a)] = Find(b);
}

void Kruskal(int E, int V){
	vector<Highway> answer; // Output vector
	answer.clear();
	answer.reserve(V - 1);

	for (int i = 0, j = 0; i < E && j < V - 1; i++){
		if (Find(highways[i].u) == Find(highways[i].v)){
			continue;
		}

		Union(highways[i].u, highways[i].v);
		answer.push_back(Highway{ highways[i].u + 1, highways[i].v + 1});
		j++;
	}

	if (answer.size() == 0){
		cout << "No new highways need\n";
	}
	else{
		for (vector<Highway>::iterator it = answer.begin(); it != answer.end(); it++){
			cout << it->u << " " << it->v << "\n";
		}
	}
}