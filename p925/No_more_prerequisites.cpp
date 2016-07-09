#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

int main() {
	// Graph Problem
	// Run time : 0.00s

	map<string, int> Id;
	map<string, vector<string>> Output;
	vector<string> tempInput;
	vector<string> tempResult;

	int C, m, n, h,
		i, j, k, index,
		cur, nex, tar;
	string temp, src, des;
	bool skippable;

	cin >> C;
	while (C--) {
		Id.clear();
		tempInput.clear();
		Output.clear();

		cin >> m;
		for (i = 0; i < m; i++) {
			cin >> temp;
			tempInput.push_back(temp);
		}

		sort(tempInput.begin(), tempInput.end());

		for (i = 0; i < m; i++)
			Id[tempInput[i]] = i;

		vector<int>* adjList = new vector<int>[m];
		bool** reachable = new bool*[m];

		for (i = 0; i < m; i++) {
			reachable[i] = new bool[m];
			adjList[i].clear();
			fill(reachable[i], reachable[i] + m, false);
		}

		cin >> n;
		for (i = 0; i < n; i++) {
			cin >> des >> h;
			for (j = 0; j < h; j++) {
				cin >> src;
				adjList[Id[src]].push_back(Id[des]);
				reachable[Id[src]][Id[des]] = true;
			}
		}

		// Map name to index
		string* name = new string[m];
		for (map<string, int>::iterator it = Id.begin(); it != Id.end(); it++) {
			name[it->second] = it->first;
			//cout << name[it->second] << " " << it->second << "\n";
		}

		// Find transitive closure
		for (k = 0; k < m; k++)
			for (cur = 0; cur < m; cur++)
				for (j = 0; j < adjList[k].size(); j++) {
					nex = adjList[k][j];
					if (reachable[cur][k]) {
						/*cout << "[" << cur << "][" << k << "]"
							<< "[" << k << "][" << nex << "]\n";*/
						reachable[cur][nex] = true;
					}
				}

		/* Delete unnecessary prerequisities.
		 * If A -> C and A -> B -> C, we need to discard A -> C
		 * which means the prerequisitiy of C is B only. */
		for (cur = 0; cur < m; cur++) {
			tempResult.clear();
			for (j = 0; j < adjList[cur].size(); j++) {
				tar = adjList[cur][j];
				skippable = false;
				for (k = 0; k < adjList[cur].size(); k++)
					if (k != j) { 
						nex = adjList[cur][k];
						if (reachable[nex][tar]) {
							/*cout << "cur = " << cur << " tar = " << tar
								<< " reachable[" << nex << "][" << tar << "]\n";*/
							skippable = true;
							break;
						}
					}
				if (!skippable) {
					//cout << "tempResult: " << name[cur] << " " << name[tar] << "\n";
					Output[name[tar]].push_back(name[cur]);
				}
			}
		}

		for (map<string, vector<string>>::iterator it = Output.begin(); it != Output.end(); it++) {
			cout << it->first << " " << it->second.size();
			for (vector<string>::iterator its = it->second.begin(); its != it->second.end(); its++)
				cout << " " << *its;

			cout << "\n";
		}

		for (i = 0; i < m; i++)
			delete[] reachable[i];
		delete[] adjList;
		delete[] reachable;
		delete[] name;

	}

	//system("pause");
	return 0;
}