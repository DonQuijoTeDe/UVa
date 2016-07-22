#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

#define MAX 10 // The max input length

char input[MAX];
char sol[MAX];
bool isUsed[MAX];
int tail;

void DFS(int);

int main() {
	int n, i;
	string temp;

	cin >> n;
	while (n--) {
		cin >> temp;
		tail = temp.length();

		for (i = 0; i < tail; i++) {
			input[i] = temp[i];
			isUsed[i] = false;
		}

		sort(input, input + tail); // Sorted in ascending order

		DFS(0);

		cout << "\n";
	}

	return 0;
}

void DFS(int head) {
	if (head == tail) {
		for (int i = 0; i < tail; i++)
			cout << sol[i];
		cout << "\n";
		return;
	}

	char last_char = '\0';
	for (int i = 0; i < tail; i++) {
		if (isUsed[i])
			continue;
		if (input[i] == last_char)
			continue;

		last_char = input[i];
		isUsed[i] = true;
		sol[head] = input[i];
		DFS(head + 1);
		isUsed[i] = false;
	}

}

/* Input :
 * aabb
 * Output :
 * aabb
 * abab
 * abba
 * baab
 * baba
 * bbaa */