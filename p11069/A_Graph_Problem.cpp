#include <iostream>
using namespace std;

int main() {
	int n, i;
	while (cin >> n && n) {

		int* DP = new int[n + 3];
		DP[1] = 1; // n1 = {(1)} = 1
		DP[2] = 2; // n2 = {(1),(2)} = 2 
		DP[3] = 2; // n3 = {(1,3),(2)} = 2
		           // n4 = {(1,3),(2,4),(1,4)} = n1 + n2 = 3
		           // n5 = {(1,3,5),(2,4),(1,4),(2,5)} = n2 + n3 = 4
                    	
		for (i = 4; i <= n; i++)
			DP[i] = DP[i - 2] + DP[i - 3];

		cout << DP[n] << "\n";

		delete[] DP;
	}
}