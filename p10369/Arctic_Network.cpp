#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

struct Point{
	int x, y;
	Point(){};
	Point(int first, int second) : x(first), y(second){}
};

struct Edge{
	int u, v;
	double cost;
};

int Find(int);
void Union(int, int);
double Kruskal(int, int, int);
void Init(int);
bool Cmp(Edge, Edge);

vector<Edge> edges;
vector<int> boss;

int main(){
	// Min Spanning Tree Problem
	// Run time : 0.03s

	int Case, S, P,
		i, j, k;
	vector<Point> points;
	edges.reserve(499*250); // At most (500,2) edges, where 500 is the number of 
	                        // points to choose from, and we choose 2 of them

	cin >> Case;
	while (Case--){
		cin >> S >> P;

		points.clear();
		points.reserve(P);
		Point t1;
		for (i = 0; i < P; i++){
			cin >> t1.x >> t1.y;
			points.push_back(t1);
		}

		edges.clear();
		Edge t2;
		for (i = 0; i < P - 1; i++){ // Calculate the distance between each pair of points
			for (j = i + 1; j < P; j++){
				t2.cost = sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2));
				t2.u = i;
				t2.v = j;
				edges.push_back(t2);
			}
		}

		boss.clear();
		boss.resize(P);
		Init(P); // vector<int> boss is for union operation

		sort(edges.begin(), edges.end(), Cmp); // Sort in increasing order

		double answer = Kruskal(edges.size(), P, S);

		cout << fixed << setprecision(2) << answer << "\n";
	}

	return 0;
}

bool Cmp(Edge a, Edge b){
	return a.cost < b.cost;
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

double Kruskal(int E, int V, int S){
	double answer;
	// We have S satellites, V points and E edges
	// If the point has a satellite, it will not
	// cost anything and hence the edges we need
	// will become (V-1)-(S-1)
	for (int i = 0, j = 0; i < E, j < (V - 1) - (S - 1); i++){
		while (Find(edges[i].u) == Find(edges[i].v)){
			i++;
		}

		Union(edges[i].u, edges[i].v);
		j++;

		answer = edges[i].cost;
	}

	return answer;
}