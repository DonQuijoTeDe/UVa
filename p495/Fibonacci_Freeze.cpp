#include <iostream>
#include <sstream>
using namespace std;

string BigIntegerAdd(string, string);

int main() {
	// Big Integer Problem
	// Run Time : 0.05s (could be optimized)
	// Reference : http://blog.tobygameac.com/2012/08/uva-495-fibonacci-freeze.html

	string DP[5001];

	DP[0] = '0';
	DP[1] = '1';

	//string temp = BigIntegerAdd("1234599999", "67891");

	for (int i = 2; i <= 5000; i++)
		DP[i] = BigIntegerAdd(DP[i - 1], DP[i - 2]);

	int number;
	while (cin >> number) {

		cout << "The Fibonacci number for " << number << " is " << DP[number] << "\n";

	}

	return 0;
}

string BigIntegerAdd(string a, string b) {
	string answer;
	int carry = 0, temp,
		digit, digitA, digitB;

	digitA = a.length();
	digitB = b.length();
	if (digitA > digitB)
		digit = digitA;
	else
		digit = digitB;

	while (digit > 0) {
		temp = carry;
		if (--digitA >= 0) {
			//cout << a[digitA] << " ";
			temp = temp + a[digitA] - '0'; // ascii code transform
		}
		if (--digitB >= 0) {
			//cout << b[digitB] << " ";
			temp = temp + b[digitB] - '0';
		}
		carry = temp / 10;
		temp %= 10;
		answer.insert(answer.begin(), temp + '0');
		//cout << answer << "\n";
		digit--;
	}
	if (carry) {
		answer.insert(answer.begin(), carry + '0');
		//cout << answer << "\n";
	}

	return answer;
}
