#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

class DisjointSet {

public:
	vector<int> parent, ranks;

	DisjointSet(int n) {
		for (int i = 0; i < n; i++) {
			parent.push_back(i);
			ranks.push_back(0);
		}
	}

	int Find(int node) {
		if (parent[node] != node)
			parent[node] = Find(parent[node]);

		return parent[node];
	}

	bool Union(int x, int y) {
		int xParent = Find(x);
		int yParent = Find(y);

		if (xParent == yParent)
			return false;

		if (ranks[xParent] < ranks[yParent])
			parent[xParent] = yParent;
		else if (ranks[xParent] > ranks[yParent])
			parent[yParent] = xParent;
		else {
			parent[yParent] = xParent;
			ranks[xParent]++;
		}

		return true;
	}
};

bool checkvalidi(int x, int y) {
	return (x >= 1 && x <= y);
}
bool checkvalidj(int x, int y) {
	return (x >= 0 && x < y);
}

string** Allocate2D(int h, int w) {

	string **array2d = new string*[h];
	for (int i = 0; i < h; i++)
		array2d[i] = new string[w];
	return array2d;
}

string** GenerateMaze(int h, int w) {

	int numOfSets, i, j, randomCell;
	numOfSets = w*h;
	DisjointSet ds(numOfSets);
	string** maze = Allocate2D(h + 1, w + 1);			// size+1 to make borders of maze

														//initialize maze
	for (int i = 0; i <= h; i++) {
		for (int j = 0; j <= w; j++) {
			if (i == 0 && j == 0)
				maze[i][j] = "  ";
			if (j != 0 && i == 0 && j != w)			// fill first row by _ and stop when j = width, Top edge
				maze[i][j] = " _";
			else if (j == w && i != 0 && i != h)	// fill last column by | except first row, Edge on right
				maze[i][j] = "|";
			else if (j != w && i != 0)
				maze[i][j] = "|_";
		}
	}

	//print initial maze
	for (int i = 0; i <= h; i++) {
		for (int j = 0; j <= w; j++)
			cout << maze[i][j];
		cout << endl;
	}

	/*Algorithm to remove wall:
	-choose random cell
	-choose neighbor which is not in the same set, and remove the wall
	-stop when all in the same set
	*/
	srand(time(0));
	while (numOfSets > 1) {

		i = rand() % h + 1;
		j = rand() % w;
		randomCell = (i - 1)*w + j;

		if (checkvalidi(i + 1, h)) {
			if (ds.Union(randomCell, (i)*w + j)) {
				if (maze[i][j] == "|_")
					maze[i][j] = "| ";
				else if (maze[i][j] == " _")
					maze[i][j] = "  ";
				numOfSets--;
				continue;
			}
		}

		if (checkvalidj(j + 1, w)) {
			if (ds.Union(randomCell, (i - 1)*w + j + 1)) {
				if (maze[i][j + 1] == "|_")
					maze[i][j + 1] = " _";
				else if (maze[i][j + 1] == "| ")
					maze[i][j + 1] = "  ";
				numOfSets--;
				continue;
			}
		}

		if (checkvalidi(i - 1, h)) {
			if (ds.Union(randomCell, (i - 2)*w + j)) {
				if (maze[i - 1][j] == "|_")
					maze[i - 1][j] = "| ";
				else if (maze[i - 1][j] == " _")
					maze[i - 1][j] = "  ";
				numOfSets--;
				continue;
			}
		}

		if (checkvalidj(j - 1, w)) {
			if (ds.Union(randomCell, (i - 1)*w + j - 1)) {
				if (maze[i][j] == "|_")
					maze[i][j] = " _";
				else if (maze[i][j] == "| ")
					maze[i][j] = "  ";
				numOfSets--;
				continue;
			}
		}
	}

	//print Generate maze
	for (int i = 0; i <= h; i++) {
		for (int j = 0; j <= w; j++)
			cout << maze[i][j];
		cout << endl;
	}

	return maze;
}

int main()
{
	int h, w;
	cout << "Enter height and width respectively: ";
	cin >> h >> w;
	GenerateMaze(h, w);

	system("pause");
	return 0;
}
