#include <iostream>
using namespace std;

int main() {
	int i, j, N;
	int DP[7490] = {0},
		Coin[] = { 1, 5, 10, 25, 50 };

	DP[0] = 1;
	for (i = 0; i < 5; i++)
		for (j = Coin[i]; j <= 7489; j++) {
			//cout << "DP[" << j << "] = " << DP[j] << " + " << DP[j - Coin[i]] << "\n";
			DP[j] = DP[j] + DP[j - Coin[i]];
		}
			

	while (cin >> N) {
		cout << DP[N] << "\n";
	}

	return 0;
}