#include <iostream>
#include <vector>
using namespace std;

vector<bool>* sieve(int n);

int main() {
	const int N = 10000000;
	vector<bool>* pNums = sieve(N);
	vector<bool>& nums = *pNums;

	int input, remainingSum;
	while (cin >> input) {
		/* use Goldbach's Conjecture */

		if (input < 8)
			cout << "Impossible.\n";
		else {
			if (input % 2 == 0) {
				cout << "2 2 ";
				remainingSum = input - 4;
			}
			else {
				cout << "2 3 ";
				remainingSum = input - 5;
			}

			for (int i = 2; i < remainingSum; i++) {
				if (nums[i] && nums[remainingSum - i]) {
					cout << i << " " << remainingSum - i << "\n";
					break;
				}
			}
		}
	}

	delete pNums;
	return 0;
}

/* the algorithm of finding prime numbers in a faster way 
 * the following algorithm could be modified in a more faster way
 * since we would mark the same non-prime number more than twice
 * and we should do some check before marking
 */
vector<bool>* sieve(int n) {
	vector<bool>* pNums = new vector<bool>(n + 1, true);
	vector<bool>& nums = *pNums;
	nums[0] = nums[1] = false;

	for (int i = 2; i*i <= n; i++) {
		if (nums[i]) {
			for (int j = 2 * i; j <= n; j += i) {
				nums[j] = false;
			}
		}
	}

	return pNums;
}