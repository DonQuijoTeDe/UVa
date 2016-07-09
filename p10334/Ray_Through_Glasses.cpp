#include <iostream>
#include <string>
using namespace std;

string BigIntegerAdd(string, string);

int main() {
	// Big Integer Problem
	// Run time : 0.00s

	int n;
	
	string DP[1001];
	DP[0] = "1";
	DP[1] = "2";
	DP[2] = "3";

	for (int i = 3; i < 1001; i++)
		DP[i] = BigIntegerAdd(DP[i - 1], DP[i - 2]);

	while (cin >> n) {

		cout << DP[n] << "\n";

	}

	return 0;
}

string BigIntegerAdd(string a, string b) {
	string answer = "";
	int digit, digitA, digitB,
		carry = 0, temp = 0;

	digitA = a.length();
	digitB = b.length();
	digit = digitA > digitB ? digitA : digitB;

	while (digit--) {
		temp = carry;
		if (--digitA >= 0) {
			temp += a[digitA] - '0';
		}
		if (--digitB >= 0) {
			temp += b[digitB] - '0';
		}
		carry = temp / 10;
		temp %= 10;
		answer.insert(answer.begin(), temp + '0');
	}
	if (carry) {
		answer.insert(answer.begin(), carry + '0');
	}

	return answer;
}