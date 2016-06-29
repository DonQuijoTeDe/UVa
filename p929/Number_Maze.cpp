#include <iostream>
#include <queue>
using namespace std;

struct Node
{
	int x, y, w;
	Node(){};
	Node(int a, int b, int c) : x(a), y(b), w(c){}
	bool operator< (const Node& n) const
	{
		return w > n.w;
	}
};

int main() {
	int Case, row, column, i, j,
		Dir[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; // right, left, down, up
	cin >> Case;

	while (Case--) {
		cin >> row >> column;

		/* --- Start --- Dynamic allocation */
		int** Maze = new int*[row];
		int** Dis = new int*[row];
		bool** isVisit = new bool*[row];

		for (i = 0; i < row; i++) {
			Maze[i] = new int[column];
			Dis[i] = new int[column];
			isVisit[i] = new bool[column];
		}
		/* --- End --- Dynamic allocation */

		for (i = 0; i < row; i++)
			for (j = 0; j < column; j++)
				cin >> Maze[i][j];

		/* --- Start --- Dijkstra */

		/* Initialization */
		for (i = 0; i < row; i++)
			for (j = 0; j < column; j++) {
				Dis[i][j] = 1e9;
				isVisit[i][j] = false;
			}

		priority_queue<Node> PQ;

		Dis[0][0] = Maze[0][0];
		PQ.push(Node(0, 0, Dis[0][0]));

		for (i = 0; i < row*column; i++) {

			/* Find the node which has the smallest distance and is
			   started from source and have not been visited yet */
			int next_x = -1, next_y = -1;
			while (!PQ.empty()) {
				Node node = PQ.top();
				PQ.pop();
				if (!isVisit[node.x][node.y]) {
					next_x = node.x;
					next_y = node.y;
					break;
				}
			}

			/* Have reached the destination */
			if (next_x == -1 || next_x == row - 1 && next_y == column - 1)
				break;

			isVisit[next_x][next_y] = true;

			/* Relaxation which needs to check 4 directions */
			for (j = 0; j < 4; j++) {
				int x = next_x + Dir[j][0], y = next_y + Dir[j][1];
					if (x > -1 && x < row && y > -1 && y < column) {
						if (Dis[next_x][next_y] + Maze[x][y] < Dis[x][y]) {
							Dis[x][y] = Dis[next_x][next_y] + Maze[x][y];
							PQ.push(Node(x, y, Dis[x][y]));
						}
					}
			}
		}

		/* --- End --- Dijkstra */

		cout << Dis[row - 1][column - 1] << "\n";

		/* --- Start --- Release allocation */
		for (i = 0; i < row; i++) {
			delete[] Maze[i];
			delete[] Dis[i];
			delete[] isVisit[i];
		}
		delete[] Maze;
		delete[] Dis;
		delete[] isVisit;
		/* --- End --- Release allocation */
	}

	//system("pause");
	return 0;
}
