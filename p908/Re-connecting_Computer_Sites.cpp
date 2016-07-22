#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Line{
	int u, v, w;
	Line(){};
	Line(int first, int second, int third) :u(first), v(second), w(third){}
};

void Init(int);
int Find(int);
void Union(int, int);
int Kruskal(int, int);
bool Cmp(Line, Line);

vector<int> Parent;
vector<Line> lines;

int main(){
	// Min Spanning Tree Problem
	// Run time : 0.00s

	int V, K, M,
		i,
		u, v, w, ori;
	bool first = true;

	while (cin >> V){
		if (first)
			first = false;
		else
			cout << "\n";

		// Original cost
		ori = 0;
		for (i = 0; i < V - 1; i++){
			cin >> u >> v >> w;
			ori += w; 
		}

		cin >> K;
		lines.clear();
		lines.reserve(K);

		Line temp;
		for (i = 0; i < K; i++){
			cin >> temp.u >> temp.v >> temp.w;
			lines.push_back(temp);
		}
		
		cin >> M;
		lines.reserve(K + M);

		for (i = 0; i < M; i++){
			cin >> temp.u >> temp.v >> temp.w;
			lines.push_back(temp);
		}

		Parent.clear();
		Parent.resize(V + 1); // Parent is a vector<int>,
		                       // preventing the tree from producing a cycle 
		Init(V);

		sort(lines.begin(), lines.end(), Cmp); // Sort in increasing order

		cout << ori << "\n" << Kruskal(V, M + K) << "\n";
	}

	return 0;
}

bool Cmp(Line a, Line b){
	return a.w < b.w;
}

void Init(int n){
	for (int i = 1; i <= n; i++){
		Parent[i] = i;
	}
}

int Find(int n){
	return n == Parent[n] ? n : (Parent[n] = Find(Parent[n]));
}

void Union(int a, int b){
	Parent[Find(a)] = Find(b);
}

int Kruskal(int V, int E){
	int answer = 0;
	for (int i = 0, j = 0; i < E && j < V - 1; i++){

		while (Find(lines[i].u) == Find(lines[i].v)){ // Check if it will produce a cycle
			i++;
		}

		Union(lines[i].u, lines[i].v); // Union the two points
		answer += lines[i].w;
		j++;
	}

	return answer;
}