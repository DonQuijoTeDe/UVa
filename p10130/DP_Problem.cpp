#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
	int price, weight;
};

int main() {
	int T, N, G, limit, output,
		i, j;

	cin >> T;
	while (T--) {
		// DP Problem
		// Run time : 0.01s

		cin >> N;
		Item* item = new Item[N];
		for (i = 0; i < N; i++)
			cin >> item[i].price >> item[i].weight;

		limit = 0;
		cin >> G;
		int* Weight = new int[G];
		for (i = 0; i < G; i++) {
			cin >> Weight[i];
			if (Weight[i] > limit)
				limit = Weight[i];
		}
		
		int** DP = new int*[N + 1];
		for (i = 0; i <= N; i++)
			DP[i] = new int[limit + 1];

		fill(DP[0], DP[0] + limit + 1, 0);
		for (i = 0; i < N; i++) // Try each kind of object
			for (j = 0; j <= limit; j++) { // Try each kind of weight
				if (j < item[i].weight) {
					DP[i + 1][j] = DP[i][j];
					/*cout << "DP[" << i + 1 << "][" << j << "] = " << DP[i][j] << "\n";*/
				}
				else {
					DP[i + 1][j] = max(DP[i][j], DP[i][j - item[i].weight] + item[i].price);
					/*cout << "DP[" << i + 1 << "][" << j << "] = max { "
					<< "DP[" << i << "][" << j << "]:" << DP[i][j]
					<< ", DP[" << i << "][" << j - item[i].weight << "]:"
					<< DP[i][j - item[i].weight] << " + " 
					<< "item[" << i << "].price:" << item[i].price << " }\n";*/
				}
			}

		// Output
		output = 0;
		for (i = 0; i < G; i++) {
			output += DP[N][Weight[i]];
		}
		cout << output << "\n";

		// Release allocation
		for (i = 0; i <= N; i++)
			delete[] DP[i];
		delete[] DP;
		delete[] Weight;
		delete[] item;
	}

	return 0;
}