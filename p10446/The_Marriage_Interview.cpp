#include <iostream>
#include <string.h>
using namespace std;

unsigned long long DP[61][61];

/*int counter;
int trib(int, int);*/

int main() {
	int n, back,
		Case = 1,
		i, j, k;
	unsigned long long temp;

	memset(DP, 0, sizeof(DP));
	fill(DP[0], DP[0] + 61, 1);
	fill(DP[1], DP[1] + 61, 1);

	/* Construct the table */
	for (i = 2; i < 61; i++)
		for (j = 0; j < 61; j++) {
			temp = 1;
			for (k = 1; k <= j; k++) {
				if (i - k > 1)
					temp += DP[i - k][j];
				else {
					temp += (j - k + 1);
					break;
				}
			}
			//cout << "DP[" << i << "][" << j << "] = " << temp << "\n";
			DP[i][j] = temp;
		}
	
	while (cin >> n >> back && n < 61 && back < 61) {
		//counter = 0;
		//trib(n, back);
		
		if (n < 0) // Special case, get RE once :(
			n = 0;

		cout << "Case " << Case++ << ": " << DP[n][back] << "\n";
	}

	return 0;
}

/*int trib(int n, int back) {
	int sum = 0;
	counter++;
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	for (int i = 1; i <= back; i++)
		sum += trib(n - i, back);

	return sum;
}*/