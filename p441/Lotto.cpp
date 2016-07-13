#include <iostream>
#include <string.h>
using namespace std;

int sol[14], input[14];
int len;

void DFS(int, int);

int main() {
	// Run time : 0.00s

	int i = 0;
	bool first = false;

	while (cin >> len && len) {
		if (first)
			cout << "\n";
		else
			first = true;

		memset(input, 0, sizeof(input));
		memset(sol, 0, sizeof(sol));

		for (i = 0; i < len; i++)
			cin >> input[i];

		DFS(0, 0);

	}

	return 0;
}

void DFS(int size, int num) {
	if (size == 6) {
		cout << sol[0];
		for (int i = 1; i < size; i++)
			cout << " " << sol[i];
		cout << "\n";
		return;
	}

	for (int i = num; i < len; i++) {
		sol[size] = input[i];
		DFS(size + 1, i + 1);
	}
}