#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int Add(string, string);

int main() {
	// Run Time : 0.02s

	int n, m, answer = 0;

	while (cin >> n >> m && n + m) {

		answer = Add(to_string(n), to_string(m));

		if (answer == 1)
			cout <<"1 carry operation.";
		else if (answer)
			cout << answer << " carry operations.";
		else
			cout << "No carry operation.";
		cout << "\n";
	}

	return 0;
}

int Add(string a, string b) {
	int answer = 0;
	int carry = 0, temp,
		digit, digitA, digitB;

	digitA = a.length();
	digitB = b.length();
	digit = digitA > digitB ? digitA : digitB;

	while (digit > 0) {
		temp = carry;
		if (--digitA >= 0) {
			//cout << a[digitA] << " ";
			temp += a[digitA] - '0'; // ascii code transform
		}
		if (--digitB >= 0) {
			//cout << b[digitB] << "\n";
			temp += b[digitB] - '0';
		}
		if (temp >= 10) {
			answer++;
		}

		carry = temp / 10;
		temp %= 10;
		digit--;
	}

	return answer;
}
