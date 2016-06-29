#include <iostream>
#include <math.h>
using namespace std;

bool Check(bool a[], int size);

int main() {
	int i, L, temp;
	bool isJolly;

	while (cin >> L) {
		isJolly = true;
		int* seq = new int[L];
		bool* record = new bool[L];

		/* Initialize and Store Input */
		for (i = 0; i < L; i++)
			record[i] = false;
		for (i = 0; i < L; i++)
			cin >> seq[i];

		/* Do Jolly Jumper Check */
		for (i = 0; i < L; i++) {
			if (i > 0) {
				temp = abs(seq[i] - seq[i - 1]);
				if (temp > 0 && temp < L && !record[temp]) {
					record[temp] = true;
				} else {
					isJolly = false;
					break;
				}
			} else
				record[0] = true;
		}

		if (isJolly && Check(record, L))
			cout << "Jolly";
		else
			cout << "Not jolly";
		cout << "\n";

		delete[] seq;
		delete[] record;
	}
}

bool Check(bool a[], int size) {
	for (int i = 0; i < size; i++)
		if (!a[i])
			return false;

	return true;
}
