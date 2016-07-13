#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <string.h>
using namespace std;

#define MAX 65

char sol[MAX], input[MAX];
bool isUsed[MAX];
int len;

bool Cmp(char, char);
void DFS(int size);

int main() {
	// Run time : 0.05s
	// You need to write your own compare funtion
	// in the following order : AaBbCcDdEe......

	int n;
	string s;

	cin >> n;
	while (n--) {
		memset(isUsed, false, sizeof(isUsed));
		memset(input, 0, sizeof(input));
		memset(sol, 0, sizeof(sol));

		cin >> s;
		len = s.length();
		strcpy(input, s.c_str());
		sort(input, input + len, Cmp); 

		DFS(0);

	}

	return 0;
}

void DFS(int size) {
	if (size == len) {
		for (int i = 0; i < size; i++)
			cout << sol[i];
		cout << "\n";
		return;
	}

	char last_cha = ' ';
	for (int i = 0; i < len; i++) {
		if (isUsed[i] || last_cha == input[i])
			continue;

		isUsed[i] = true;
		last_cha = input[i];
		sol[size] = input[i];
		DFS(size + 1);
		isUsed[i] = false;
	}
}

bool Cmp(char right, char left) {
	char lower_right = tolower(right), lower_left = tolower(left);

	if (lower_left == lower_right) 
		return right < left;
	else
		return lower_right < lower_left;
}