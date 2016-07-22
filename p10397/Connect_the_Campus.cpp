#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

struct Point{
	int x, y;
	Point(){};
};

struct Road{
	int u, v;
	double cost;
};

bool Cmp(Road, Road);
void Union(int, int);
void Init(int);
int Find(int);
double Kruskal(int, int);

vector<Road> roads;
vector<int> boss;

int main(){
	/* Min Spanning Tree Problem
	   Run time: 0.06s

	   Critical Case
	   Input:        Output:
	   4             14.05
	   -10 0
     10 0
	   0 3
	   0 - 1
	   1
	   1 2                    */

	int N, M, u, v,
		i, j, k;

	vector<Point> points;
	roads.reserve(375 * 749); // At most (750,2) edges, where 750 is the number of
	                          // points to choose from, and we choose 2 of them

	while (cin >> N){

		points.clear();
		points.reserve(N);
		Point tmp1;
		for (i = 0; i < N; i++){
			cin >> tmp1.x >> tmp1.y;
			points.push_back(tmp1);
		}

		roads.clear();
		Road tmp2;
		for (i = 0; i < N - 1; i++){ // The distance between two buildings
			for (j = i + 1; j < N; j++){
				tmp2.cost = sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2));
				tmp2.u = i;
				tmp2.v = j;
				roads.push_back(tmp2);
			}
		}

		boss.clear();
		boss.resize(N);
		Init(N); // Initialize each building's boss

		cin >> M;
		for (i = 0; i < M; i++){
			cin >> u >> v;
			if (u > v){
				swap(u, v);
			}
		    boss[Find(u - 1)] = Find(v - 1); // Key point: Union the existed edges first
		}

		sort(roads.begin(), roads.end(), Cmp);

		double answer = Kruskal(roads.size(), N);

		cout << setprecision(2) << fixed << answer << "\n";
	}

	return 0;
}

void Init(int n){
	for (int i = 0; i < n; i++){
		boss[i] = i;
	}
}

int Find(int n){
	return n == boss[n] ? n : boss[n] = Find(boss[n]);
}

void Union(int a, int b){
	boss[Find(a)] = Find(b);
}

bool Cmp(Road a, Road b){
	return a.cost < b.cost;
}

double Kruskal(int E, int V){
	double answer = 0;
	for (int i = 0, j = 0; i < E && j < V - 1; i++){
		if (Find(roads[i].u) == Find(roads[i].v)){
			continue;
		}
		Union(roads[i].u, roads[i].v);
		answer += roads[i].cost;
		j++;
	}

	return answer;
}
