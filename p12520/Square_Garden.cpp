#include <iostream>
using namespace std;

int main() {
	long long L, M, N, tN, answer, tanswer;
	while (cin >> L >> N && L) {
		M = L*L / 2 + L % 2; /* Possible maximum */

		if (N <= M) {
			cout << 4 * N;
		}
		else {
			/* Check whether L is odd or even */
	        switch (L % 2) {
				/* If L is odd */
			    case 1 :
					tN = N;
					/* First situation */
					answer = 4 * M;
					N -= M;
					if (N > 4 * (L / 2)) {
						answer -= 2 * 4 * (L / 2);
						N -= 4 * (L / 2);
						answer -= 4 * N;
					}
					else
						answer -= 2 * N;

					/* Second situation */
					tanswer = 4 * (M - 1);
					tN -= (M - 1);
					if (tN > 4) tN -= 4;
					else tN = 0;
					if (tN > 4 * (L / 2 - 1)) {
						tanswer -= 2 * 4 * (L / 2 - 1);
						tN -= 4 * (L / 2 - 1);
						tanswer -= 4 * tN;
					}
					else
						tanswer -= 2 * tN;

					/* To check whick answer is larger */
					if (answer > tanswer) cout << answer;
					else cout << tanswer;

					break;

				/* If L is even */
				default :
					answer = 4 * M;
					N -= M;
					if (N > 2) N -= 2;
					else N = 0;
					if (N > 4 * (L / 2 - 1)) {
						answer -= 2 * 4 * (L / 2 - 1);
						N -= 4 * (L / 2 - 1);
						answer -= 4 * N;
					}
					else
						answer -= 2 * N;

					cout << answer;
			}
		}
		cout << "\n";
	}

	return 0;
}