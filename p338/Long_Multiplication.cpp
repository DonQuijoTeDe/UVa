#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

struct PartialResult {
	string str;
	int move;
} num[10];

int aligned;

string BigIntegerMul(string, string);
string BigIntegerAdd(string, string);
string AdjustFormat(string a, int);

int main() {
	// We can treat it as a big integer problem
	// Use string operation to solve it
	// Run time : 0.05s

	int i, digit, check, checkline;
	long long x, y; // The input is <= 10 digits
	string answer, firstline, secondline, X, Y;

	while (scanf("%lld %lld", &x, &y) == 2) {

		X = to_string(x);
		Y = to_string(y);

		firstline = "", secondline = "";
		digit = X.length() > Y.length() ? X.length() : Y.length();

		// Initialize
		for (i = 0; i < 10; i++) {
			num[i].str = "";
			num[i].move = 0;
		}

		answer = BigIntegerMul(X, Y); // Compute X*Y
		aligned = answer.length(); // Need to be aligned

		// Output format
		cout << AdjustFormat(X, 0) << "\n" << AdjustFormat(Y, 0) << "\n";
		for (i = 0; i < digit; i++)
			firstline.insert(firstline.begin(), '-');
		cout << AdjustFormat(firstline, 0);

		if (X != "0" && Y != "0") {
			if (digit == 1)
				cout << "\n" << answer;
			else {
				check = 0, checkline = 0;
				for (i = 0; i < Y.length(); i++) {
					if (Y[Y.length() - 1 - i] - '0' == 0) {
						check++;
						continue;
					}
					if (check == Y.length() - 1) {
						checkline = 1;
						break;
					}
					cout << "\n" << AdjustFormat(num[i].str, num[i].move);
				}
				if (!checkline) {
					for (i = 0; i < aligned; i++)
						secondline.insert(secondline.begin(), '-');
					cout << "\n" << secondline;
				}
				cout << "\n" << answer;
			}
		} else
			cout << "\n" << AdjustFormat("0", 0);

		cout << "\n\n";
		
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

		num[k].str = partial; // Store Partial Result
		num[k].move = k;
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

string AdjustFormat(string a, int move) {
	int i, digit = a.length();

	if (move == 0) {
		for (i = 0; i < aligned - digit; i++)
			a.insert(a.begin(), ' ');
		return a;

	} else {
		a.erase(digit - move, move);
		for (i = 0; i < aligned - digit; i++)
			a.insert(a.begin(), ' ');
		return a;
	}
}