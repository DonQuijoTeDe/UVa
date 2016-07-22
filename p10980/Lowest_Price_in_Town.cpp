#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Combo {
	int number;
	double price;
};

int main() {
	double unit;
	int M, K, limit,
		i, j, k, Case = 0;
	string temp;

	vector<int> seq;

	while (cin >> unit >> M) {
		// DP Problem

		Combo* combo = new Combo[M + 1];
		combo[0].number = 1;
		combo[0].price = unit;
		for (i = 1; i < M + 1; i++) {
			cin >> combo[i].number >> combo[i].price;
		}

		seq.clear();
		limit = 0;
		cin.ignore();
		getline(cin, temp);
		stringstream ss(temp);
		while (ss >> K) {
			seq.push_back(K);
			if (K > limit)
				limit = K;
		}

		double* DP = new double[limit + 1];
		fill(DP, DP + limit + 1, 1e9);
		DP[0] = 0;
		// Try all kinds of numbers
		for (i = 1; i <= limit; i++) {
			// Try all kinds of schemes
			for (j = 0; j < M + 1; j++) { 
				DP[i] = min(DP[i], (i + combo[j].number - 1) / combo[j].number * combo[j].price);
				// Try all kinds of combinations
				for (k = 1; k <= combo[j].number; k++) { 
					if (i - k >= 0) {
						DP[i] = min(DP[i], DP[i - k] + combo[j].price);
					}
				}
			}
		}

		Case++;
		cout << "Case " << Case << ":";
		for (i = 0; i < (int)seq.size(); i++) {
			cout << "\nBuy " << seq[i]
				<< " for $"
				<< setprecision(2)
				<< fixed
				<< DP[seq[i]];
		}
		cout << "\n";

		delete[] DP;
		delete[] combo;
	}

	return 0;
}