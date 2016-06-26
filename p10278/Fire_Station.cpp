#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
	int Case, f, i,
		j, k, m, index1, index2, value;
	cin >> Case;
	while (Case--) {
		cin >> f >> i;
		i++;

		/* --- Start --- Dynamic allocation */
		int* Fire = new int[f];
		int* SF = new int[i];
		int** Dis = new int*[i];
		for (j = 1; j < i; j++)
			Dis[j] = new int[i];
		/* --- End --- Dynamic allocation */

		/* Initialize */
		for (j = 1; j < i; j++) {
			for (k = 1; k < i; k++)
				Dis[j][k] = 1e6;
			Dis[j][j] = 0;
		}

		/* Store Input */
		for (j = 0; j < f; j++)
			cin >> Fire[j];
		string str;
		getline(cin, str);
		while (getline(cin, str) && !str.empty()) {
			stringstream ss(str);
			ss >> index1 >> index2 >> value;
			Dis[index1][index2] = value;
			Dis[index2][index1] = value;
		}

		/* --- Start --- Floyd Warshall */
		for (k = 1; k < i; k++)
			for (j = 1; j < i; j++)
				for (m = 1; m < i; m++) {
					if (Dis[j][k] + Dis[k][m] < Dis[j][m])
						Dis[j][m] = Dis[j][k] + Dis[k][m];
				}
		/* --- End --- Floyd Warshall */

		/* 1. Calculate the min distance for each SF[j]
		 *    ( SF[j] means the shortest distance from 
		 *    point j to the nearest fire station )
		 * 2. Find the max distance in SF[j] and store
		 *    it in max_SF */
		int max_SF = 0;
		for (j = 1; j < i; j++) {
			SF[j] = 1e6;
			for (k = 0; k < f; k++)
				SF[j] = min(SF[j], Dis[j][Fire[k]]);
			max_SF = max(max_SF, SF[j]);
		}

		/* 1. Check whether the new fire station which would 
		 *    be built in each point could make the max_SF 
		 *    more smaller
		 * 2. If so, updates the max_SF and records it */
		int temp_max, temp_SF, answer = 1;
		for (j = 1; j < i; j++) {
			temp_max = 0;
			for (k = 1; k < i; k++) {
				temp_SF = min(SF[k], Dis[k][j]);
				temp_max = max(temp_max, temp_SF);
			}
			if (temp_max < max_SF) {
				max_SF = temp_max;
				answer = j;
			}
		}

		cout << answer << "\n";
		if (Case) cout << "\n";

		/* Release allocation */
		for (j = 1; j < i; j++)
			delete[] Dis[j];
		delete[] Dis, Fire, SF;
	}

	//system("pause");
	return 0;
}