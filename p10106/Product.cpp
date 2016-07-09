#include <iostream>
#include <string>
using namespace std;

string BigIntegerMul(string, string);
string BigIntegerAdd(string, string);

int main() {
	// Big Integer Problem
	// Run Time : 0s

	string X, Y;

	while (cin >> X >> Y) {
		if (X == "0" || Y == "0") // special case
			cout << "0";
		else
			cout << BigIntegerMul(X, Y);

		cout << "\n";
	}

	return 0;
}

string BigIntegerMul(string a, string b) {
	string partial, answer;
	int carry, temp,
		digitA, digitB,
		i, j, k;

	digitA = a.length();
	digitB = b.length();

	answer = "";
	for (i = digitB - 1, k = 0; i >= 0; i--, k++) {
		carry = temp = 0;
		partial = "";
		for (j = k; j > 0; j--)
			partial.insert(partial.begin(), '0');

		for (j = digitA - 1; j >= 0; j--) {
			temp = carry + (b[i] - '0') * (a[j] - '0');
			carry = temp / 10;
			temp %= 10;
			partial.insert(partial.begin(), temp + '0');
		}
		if (carry)
			partial.insert(partial.begin(), carry + '0');
		//cout << partial << "\n";

		if (k)
			answer = BigIntegerAdd(answer, partial);
		else
			answer = partial;
		//cout << answer << "\n";
	}

	return answer;
}

string BigIntegerAdd(string a, string b) {
	string answer = "";
	int carry = 0, temp,
		digit, digitA, digitB;

	digitA = a.length();
	digitB = b.length();
	digit = digitA > digitB ? digitA : digitB;

	while (digit--) {
		temp = carry;
		if (--digitA >= 0) {
			//cout << a[digitA] << " ";
			temp += a[digitA] - '0'; // ascii code transform
		}
		if (--digitB >= 0) {
			//cout << b[digitB] << "\n";
			temp += b[digitB] - '0';
		}
		carry = temp / 10;
		temp %= 10;
		answer.insert(answer.begin(), temp + '0');
		//cout << answer << "\n";
	}
	if (carry) {
		answer.insert(answer.begin(), carry + '0');
		//cout << answer << "\n";
	}

	return answer;
}

/*
 * Input :
 * 1698978606
 * 984130093
 * Output:
 * 1672015973527790358
 */
