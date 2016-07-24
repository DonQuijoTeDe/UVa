#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

struct Line{
	int u, v;
	double w;
	Line(){};
};

struct Freckle{
	double x, y;
	Freckle(){};
};

bool Cmp(Line, Line);
void Init(int);
int Find(int);
void Union(int, int);
double Kruskal(int, int);

vector<Line> lines;
vector<int> boss;

int main(){
	// Min Spanning Tree Problem
	// Run time : 0.00s

	int Case, N,
		i, j;
	bool first = true;

	lines.reserve(50 * 98); // At most (100,2) edges, where 100 is the number of
	                        // points to choose from, and we choose 2 of them
	vector<Freckle> freckles;

	cin >> Case;
	while (Case--){
		if (first) // presentation error :(
			first = false;
		else
			cout << "\n";

		cin >> N;
		freckles.clear();
		freckles.reserve(N);
		Freckle tmp1;
		for (i = 0; i < N; i++){
			cin >> tmp1.x >> tmp1.y;
			freckles.push_back(tmp1);
		}

		lines.clear();
		Line tmp2;
		for (i = 0; i < N - 1; i++){ // The distance between two freckles
			for (j = i + 1; j < N; j++){
				tmp2.w = sqrt(pow(freckles[i].x - freckles[j].x, 2) + pow(freckles[i].y - freckles[j].y, 2));
				tmp2.u = i;
				tmp2.v = j;
				lines.push_back(tmp2);
			}
		}

		boss.clear();
		boss.resize(N);
		Init(N);

		// There are 2 data structures can be used: vector or list.
		// List is implemented in doubled-linked-list, so when we use
		// std::sort, it will cost more resource to maintain its information
		// So I choose to use vector instead. But the advantage of list is
		// that when we are doing insertion or deletion anywhere in the 
		// structures, it will be faster than vector. If you want to access
		// elements randomly, you need to use vector
		sort(lines.begin(), lines.end(), Cmp); 

		cout << fixed << setprecision(2) << Kruskal(lines.size(), N) << "\n";
	}

	return 0;
}

void Init(int n){
	for (int i = 0; i < n; i++){
		boss[i] = i;
	}
}

bool Cmp(Line a, Line b){
	return a.w < b.w;
}

int Find(int n){
	return n == boss[n] ? n : boss[n] = Find(boss[n]);
}

void Union(int a, int b){
	boss[Find(a)] = Find(b);
}

double Kruskal(int E, int V){
	double answer = 0;
	for (int i = 0, j = 0; i < E && j < V - 1; i++){
		if (Find(lines[i].u) == Find(lines[i].v)){
			continue;
		}

		Union(lines[i].u, lines[i].v);
		j++;
		answer += lines[i].w;
	}

	return answer;
}