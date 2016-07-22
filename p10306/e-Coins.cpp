#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct Ecoin {
	int con, tec;
};

int main() {
	int n, m, S, i, j, k, answer;

	cin >> n;
	while (n--) {
		cin >> m >> S;

		int DP[301][301];
		Ecoin* ecoin = new Ecoin[m];

		for (i = 0; i < m; i++)
			cin >> ecoin[i].con >> ecoin[i].tec;

		for (i = 0; i <= S; i++)
			fill(DP[i], DP[i] + S + 1, 1e9);

		DP[0][0] = 0;
		// Try each kind of ecoins
		for (i = 0; i < m; i++) {
			// Try the conventional value of each ecoin
			for (j = ecoin[i].con; j <= S; j++) { 
				// Try the technological value of each ecoin
				for (k = ecoin[i].tec; k <= S; k++) { 
					//cout << "DP[" << j << "][" << k << "]:" << DP[j][k]
						//<< " ,DP[" << j - ecoin[i].con << "]["
						//<< k - ecoin[i].tec << "]:" << DP[j - ecoin[i].con][k - ecoin[i].tec]
						//<< "+1\n";
					DP[j][k] = min(DP[j][k], DP[j - ecoin[i].con][k - ecoin[i].tec] + 1);
				}
			}
		}
		
		answer = 1e9;
		for (i = 0; i <= S; i++) {
			for (j = 0; j <= S; j++) {
				if (sqrt(i*i + j*j) == S && DP[i][j] != 1e9) {
					// it would be more than one solution
					// choose the minimum one
					answer = min(answer, DP[i][j]);
				}
			}
		}

		if (answer != 1e9)
			cout << answer;
		else
			cout << "not possible";
		cout << "\n";

		delete[] ecoin;
	}

	return 0;
}