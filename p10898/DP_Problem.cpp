#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct Combo {
	Combo() {
		for (int i = 0; i < 6; i++)
			number[i] = 0;
	};
	int number[6];
	int price = 0;
};

int main() {
	int I, N, query,
		i, j, k, temp, exceed, current, next;

	while (cin >> I) {
		// DP Problem
		// Run time : 1.01s
		// Reference : http://blog.tobygameac.com/2013/09/uva-10898-combo-deal.html

		int* quantity = new int[I];
		for (i = 0; i < I; i++) {
			cin >> quantity[i];
		}
		
		// There would be N+I combos
		// e.g. if there are 4 items and 2 combo deals and
		// item A costs 349, B for 99, C for 109, D for 219
		// which means combo A is 1 0 0 0 349, combo B is
		// 0 1 0 0 99, combo C is 0 0 1 0 109 and combo D is
		// 0 0 0 1 219, so the total combos is 4+2=8
		// The pros is we can reduce the dimensions of DP table
		cin >> N;
		Combo* combo = new Combo[N + I];
		for (i = 0; i < I; i++) {
			combo[i].number[i] = 1;
			combo[i].price = quantity[i];
		}
		for (i = I; i < N + I; i++) {
			for (j = 0; j < I; j++) {
				cin >> combo[i].number[j];
			}
			cin >> combo[i].price;
		}

		// e.g. DP[9680] means the min price of 9, 6, 8, 0 combinations
		int p = (int)pow(10, I);
		int* DP = new int[p];
		for (i = 0; i < p; i++) { 
			DP[i] = (int)1e9; // We want the min price so we initialize it to infinite
		}

		DP[0] = 0;
		for (current = 0; current < p; current++) { // Try all kinds of items

			int* cur = new int[I];
			for (j = 0; j < I; j++) {
				cur[j] = 0;
			}

			// If current items are 2110, we store it as
			// cur[0]=2, cur[1]=1, cur[2]=1 and cur[3]=0
			temp = current;
			for (j = I - 1; j >= 0; j--) {
				cur[j] = temp % 10;
				temp /= 10;
				if (!temp) {
					break;
				}
			}

			for (j = 0; j < N + I; j++) { // Try all kinds of combos

				int* nex = new int[I];
				for (k = 0; k < I; k++) {
					nex[k] = 0;
				}

				// The function of nex[] is similar to cur[]
				next = 0;
				exceed = false;
				for (k = 0; k < I; k++) {
					nex[k] = cur[k] + combo[j].number[k];
					next = next * 10 + nex[k];
					if (nex[k] >= 10) {
						exceed = true;
						break;
					}
				}

				if (exceed) {
					delete[] nex;
					continue;
				}

				DP[next] = min(DP[next], DP[current] + combo[j].price);
				delete[] nex;
			}

			delete[] cur;
		}
		//cout << DP[9680] << " " << DP[9685];
		
		// Output
		cin >> query;
		for (i = 0; i < query; i++) {
			next = current = 0;
			for (j = 0; j < I; j++) {
				cin >> current;
				next = next * 10 + current;
			}
			cout << DP[next] << "\n";
		}

		delete[] quantity;
		delete[] combo;
		delete[] DP;

	}

	return 0;
}