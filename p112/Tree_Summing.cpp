#include <iostream>
using namespace std;

int sum;
bool isMatched;

bool DFS(int); // Depth first search

int main() {
	// Reference : https://github.com/igorbonadio/uva/blob/master/112/112.cpp

	while (cin >> sum) {
		isMatched = false;

		DFS(0);

		cout << (isMatched ? "yes\n" : "no\n");
	}

	return 0;
}

bool DFS(int acc) {
	int root;

	// peek(): Returns the next character in the input sequence, without extracting it
	while (cin.peek() == ' ' || cin.peek() == '\n')
		cin.ignore(1);

	cin.ignore(1); // '('

	while (cin.peek() == ' ' || cin.peek() == '\n')
		cin.ignore(1);

	if (cin.peek() == ')') {
		cin.ignore(1); // ')'
		return acc == sum ? true : false;
	} else {
		if (cin.peek() == '-') {
			cin.ignore(1); // '-'
			cin >> root;
			root *= -1;
		} else {
			cin >> root;
		}
		acc += root;
	}

	// Recursive call: left child and right child
	bool left = DFS(acc);
	bool right = DFS(acc);
	if (left && right)
		isMatched = true;
	
	while (cin.peek() == ' ' || cin.peek() == '\n')
		cin.ignore(1);

	cin.ignore(1); // ')'

	return false;
}
	