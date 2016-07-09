#include <iostream>
#include <sstream>
#include <string.h>
#include <algorithm>
using namespace std;

/* DFS would use recursive, so I choose to 
 * declare them at global scope, otherwise,
 * I usually allocate memories dynamically */

int Dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } },
    R, C,
    Table[100][100], 
    DP[100][100];   

int DFS(int, int);

int main() {
	int N, answer,
		i, j;
	string name;

	cin >> N;
	while (N--) {
		cin >> name >> R >> C;

		memset(Table, 0, sizeof(Table));
		memset(DP, 0, sizeof(DP));

		for (i = 0; i < R; i++)
			for (j = 0; j < C; j++)
				cin >> Table[i][j];

		answer = 0;

		/* Use DFS to calculate the longest run for each point.
		 * Or you can try using stack directly instead of recursive.
		 * But I think recursive could make your code more clearly */
		for (i = 0; i < R; i++)
			for (j = 0; j < C; j++)
				answer = max(DFS(i, j), answer);

		cout << name << ": " << answer << "\n";
	}

	//system("pause");

	return 0;
}

int DFS(int x, int y) {

	// We've checked this point, then return 
	if (DP[x][y]) 
		return DP[x][y];

	DP[x][y] = 1;


	// For each node(x, y),
	// check 4 directions up, down, left, right respectively
	// and determine which way can go to the farthest
	int i, next_x, next_y;
	for (i = 0; i < 4; i++) {
		next_x = x + Dir[i][0];
		next_y = y + Dir[i][1];
		if (next_x > -1 && next_x < R && next_y > -1 && next_y < C) // boundary check
			if (Table[next_x][next_y] < Table[x][y]) {
				/*cout << "Now:[" << x << "][" << y << "] = " << Table[x][y]
					<< " Next:[" << next_x << "][" << next_y << "] = " << Table[next_x][next_y] << "\n";*/
				DP[x][y] = max(DFS(next_x, next_y) + 1, DP[x][y]);
			}
	}

	return DP[x][y];
}