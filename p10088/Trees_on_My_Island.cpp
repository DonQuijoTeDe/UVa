#include <iostream>
#include <cmath>
using namespace std;

struct Node {
	long long x, y;
};

long long gcd(long long x, long long y) {
	if (x == 0)  return y;
	if (y == 0)  return x;
	long long t;
	while (x%y) {
		t = x; 
		x = y;
		y = t%y;
	}
	return y;
}

int main() {
	long long area, b;
	int N, i;
	Node P[1005];
	while (cin >> N && N) {
		/* Store Input */
		for (i = 0; i < N; i++)
			cin >> P[i].x >> P[i].y;
		P[N] = P[0];

		/* Calculate the area using outer product */
		area = 0;
		for (i = 0; i < N; i++)
			area += (P[i].x*P[i + 1].y) - (P[i].y*P[i + 1].x);
		if (area < 0)    area = -area;

		/* Calculate the points on each edge using the difference with gcd */
		b = 0;
		for (i = 0; i < N; i++)
			b += gcd(abs(P[i].x - P[i + 1].x), abs(P[i].y - P[i + 1].y)) - 1;
		b += N;

		/* area = i + b/2 - 1 */
		cout << (area + 2 - b) / 2 << "\n";
	}
	return 0;
}