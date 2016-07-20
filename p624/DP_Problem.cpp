#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	// DP Problem
	// Run time : 0.00s

	int W, N,
		i, j;

	while (cin >> W) {
		cin >> N;
		
		int* Tracks = new int[N + 1];
		int** DP = new int*[N + 1];

		for (i = 0; i < N; i++)
			cin >> Tracks[i];

		for (i = 0; i <= N; i++) {
			DP[i] = new int[W + 1];
			fill(DP[i], DP[i] + W + 1, 0);
		}

		for (i = 0; i < N; i++) // Try every kind of track
			for (j = 0; j <= W; j++) { // Try every kind of weight
				if (j - Tracks[i] < 0) {
					DP[i + 1][j] = DP[i][j];
					/*cout << "DP[" << i + 1 << "][" << j << "] = " << DP[i][j] << "\n";*/
				} else {
					DP[i + 1][j] = max(DP[i][j], DP[i][j - Tracks[i]] + Tracks[i]);
					/*cout << "DP[" << i + 1 << "][" << j << "] = max { "
						<< "DP[" << i << "][" << j << "]:" << DP[i][j]
						<< ", DP[" << i << "][" << j - Tracks[i] << "]:"
						<< DP[i][j - Tracks[i]] << " + " << "Tracks[" << i << "]:" << Tracks[i] << " }\n";*/
				}
			}

		// Tracking sequence
		vector<int> seq;
		for (i = N - 1, j = W; i >= 0; i--) {
			if (j - Tracks[i] >= 0 && DP[i + 1][j] == DP[i][j - Tracks[i]] + Tracks[i]) {
				seq.push_back(Tracks[i]);
				j -= Tracks[i];
			}
		}

		// Output
		for (vector<int>::reverse_iterator it = seq.rbegin(); it != seq.rend(); it++) {
			cout << *it << " ";
		}
		cout << "sum:" << DP[N][W] << "\n";

		for (i = 0; i <= N; i++)
			delete[] DP[i];
		delete[] Tracks;
		delete[] DP;

	}

	return 0;
}