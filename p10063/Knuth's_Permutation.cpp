#include <iostream>
#include <string>
using namespace std;

int len;
string input;

void DFS(string, int);

int main() {
	// Run time : 0.03s

	string left, right;
	bool line = false;

	while (cin >> input) {
		if (line)
			cout << "\n";
		else
			line = true;

		len = input.length();

		DFS("", 0);

	}

	return 0;
}

void DFS(string str, int n) {
	if (str.length() == len) {
		cout << str << "\n";
		return;
	}

	string temp; // std::insert will change the value of string
	for (int i = 0; i <= n; i++) {
		temp = str;
		DFS(temp.insert(i, input.substr(n, 1)), n + 1);
	}

}