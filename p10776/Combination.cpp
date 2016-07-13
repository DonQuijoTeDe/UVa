#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

char sol[31], input[31];
int r, len;

void DFS(int, int);

int main() {
	// Run time : 0.00s

	string s;
	int i;

	while (cin >> s >> r) {
		len = s.length();
		strcpy(input, s.c_str()); // Make sure your buffer is large enough to
		                          // handle the string's length
		                         
		sort(input, input + len);

		DFS(0, 0);

	}

	return 0;
}

void DFS(int size, int num) {
	if (size == r) {
		for (int i = 0; i < size; i++)
			cout << sol[i];
		cout << "\n";
		return;
	}

	char last_char = ' ';
	for (int i = num; i < len; i++) {
		if (last_char == input[i])
			continue;

		last_char = input[i];
		sol[size] = input[i];
		DFS(size + 1, i + 1);
	}

}