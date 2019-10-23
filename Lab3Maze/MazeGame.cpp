#include <iostream>
#include <ctime>


using namespace std;

const int numRows = 15;
const int numCols = 15;
int numOfPlants = 10;
int numOfWalkers = 15;
char plantsCanGrow = 'a';
char block = 219;

void drawMaze(char mz[numRows][numCols], int numRows, int numCols) {
	for (int row = 0; row < numRows; row++)
	{
		cout << "	";
		for (int col = 0; col < numCols; col++)
		{
			cout << mz[row][col];
		}
		cout << endl;
	}

}

void placePlant(char mz[numRows][numCols]) {
	int count = 0;
	while (count < numOfPlants) {
		int row = rand() % (numRows - 1) + 1;
		int col = rand() % (numCols - 1) + 1;

		if (mz[row][col] == ' ') {
			mz[row][col] = 'y';
			count++;
		}
	}
}

void placeWalker(char mz[numRows][numCols]) {
	int count = 0;
	while (count < numOfWalkers) {
		int row = rand() % (numRows - 1) + 1;
		int col = rand() % (numCols - 1) + 1;

		if (mz[row][col] == ' ') {
			mz[row][col] = '2';
			count++;
		}
	}
}

void plantsGrow(char mz[numRows][numCols], int aR, int aC) {
	for (int adjRow = aR - 1; adjRow <= aR + 1; adjRow++) {
		for (int adjCol = aC - 1; adjCol <= aC + 1; adjCol++) {
			//Only move to position with ' '
			if (mz[adjRow][adjCol] == ' ') {
				int willGrow = rand() % 10 + 1;
				if (willGrow == 10) {
					mz[adjRow][adjCol] = '?';//Placeholder to avoid new plant growing same turn
					numOfPlants++;
				}
			}
		}
	}
}

void changePlants(char mz[numRows][numCols]) {
	int canChange = 1;
	int plantReached = 0;

	for (int arrRow = 1; arrRow < numRows - 1; arrRow++) {
		for (int arrCol = 1; arrCol < numCols - 1; arrCol++) {
			if (mz[arrRow][arrCol] >= 'a' && mz[arrRow][arrCol] <= 'y') {
				for (int checkRow = 1; checkRow < numRows-1; checkRow++) {

					if (checkRow == arrRow) {
						plantReached = 1;
					}
					if (checkRow == arrRow && canChange == 0) {
						break;
					}
					else if (mz[checkRow][arrCol] == '2' && plantReached == 0) {
						canChange = 0;
					}
					else if (mz[checkRow][arrCol] == block && plantReached == 0) {
						canChange = 1;
					}
					else if (mz[checkRow][arrCol] == '2' && plantReached == 1) {
						canChange = 0;
						break;
					}
					else if (mz[checkRow][arrCol] == block && plantReached == 1 && canChange == 1) {
						break;
					}
				}
				//If canChange ==0, no need for second loop
				if (canChange == 1) {
					plantReached = 0;
					for (int checkCol = 1; checkCol < numCols-1; checkCol++) {

						if (checkCol == arrCol) {
							plantReached = 1;
						}
						if (checkCol == arrCol && canChange == 0) {
							break;
						}
						else if (mz[arrRow][checkCol] == '2' && plantReached == 0) {
							canChange = 0;
						}
						else if (mz[arrRow][checkCol] == block && plantReached == 0) {
							canChange = 1;
						}
						else if (mz[arrRow][checkCol] == '2' && plantReached == 1) {
							canChange = 0;
							break;
						}
						else if (mz[arrRow][checkCol] == block && plantReached == 1 && canChange == 1) {
							break;
						}
					}
				}
				if (canChange == 1) {
					if (mz[arrRow][arrCol] == 'a') {
						mz[arrRow][arrCol] = 'y';
					}
					else {
						mz[arrRow][arrCol]--;
					}
					if (plantsCanGrow == 'y') {
						plantsGrow(mz, arrRow, arrCol);
					}
				}
			}
		}
	}
	for (int arrRow = 1; arrRow < numRows - 1; arrRow++) {
		for (int arrCol = 1; arrCol < numCols - 1; arrCol++) {
			if (mz[arrRow][arrCol] == '?') {
				mz[arrRow][arrCol] = 'y';
			}
		}
	}
}

void moveWalker(char mz[numRows][numCols]) {
	for (int arrRow = 1; arrRow < numRows - 1; arrRow++) {
		for (int arrCol = 1; arrCol < numCols - 1; arrCol++) {
			if (mz[arrRow][arrCol] == '2') {
				int findSpace = 0;
				//Check if any free space exists
				for (int adjRow = arrRow - 1; adjRow <= arrRow + 1; adjRow++) {
					for (int adjCol = arrCol - 1; adjCol <= arrCol + 1; adjCol++) {
						if (mz[adjRow][adjCol] != block && mz[adjRow][adjCol] != '2' && mz[adjRow][adjCol] != 'X') {
							findSpace = 1;
							break;
						}
					}
					if (findSpace == 1) {
						break;
					}
				}
				//Randomly choose free space
				if (findSpace == 1) {
					int row = rand() % 3 + (arrRow - 1);
					int col = rand() % 3 + (arrCol - 1);
					while (mz[row][col] == block || mz[row][col] == '2' || mz[row][col] == 'X') {
						row = rand() % 3 + (arrRow - 1);
						col = rand() % 3 + (arrCol - 1);
					}
					if (mz[row][col] != ' ') {
						numOfPlants--;
					}
					mz[row][col] = 'X';//Placeholder to avoid double movement
					mz[arrRow][arrCol] = ' ';
				}
			}
		}
	}
	//Change placeholders to 2's
	for (int arrRow = 1; arrRow < numRows; arrRow++) {
		for (int arrCol = 1; arrCol < numCols; arrCol++) {
			if (mz[arrRow][arrCol] == 'X') {
				mz[arrRow][arrCol] = '2';
			}
		}
	}
}

int main() {
	
	srand(time(NULL));
	
	char  maze[numRows][numCols] = {{block,block,block,block,block,block,block,block,block,block,block,block,block,block,block},
									{block,  ' ',block,  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',block,  ' ',  ' ',block},
									{block,  ' ',  ' ',  ' ',block,block,block,block,  ' ',block,  ' ',block,  ' ',block,block},
									{block,  ' ',block,  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',block,  ' ',  ' ',  ' ',  ' ',block},
									{block,  ' ',block,block,block,block,  ' ',block,  ' ',block,block,  ' ',block,  ' ',block},
									{block,  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',block,  ' ',  ' ',  ' ',  ' ',block,  ' ',block},
									{block,  ' ',block,block,block,block,block,block,  ' ',block,block,  ' ',block,  ' ',block},
									{block,  ' ',  ' ',  ' ',block,  ' ',  ' ',  ' ',  ' ',block,  ' ',  ' ',  ' ',  ' ',block},
									{block,  ' ',block,  ' ',  ' ',  ' ',  ' ',block,  ' ',  ' ',  ' ',block,block,  ' ',block},
									{block,  ' ',block,block,block,  ' ',block,block,  ' ',block,block,block,  ' ',  ' ',block},
									{block,  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',block,  ' ',  ' ',  ' ',  ' ',  ' ',block,block},
									{block,  ' ',block,block,block,block,  ' ',block,  ' ',block,  ' ',block,  ' ',  ' ',block},
									{block,  ' ',  ' ',  ' ',  ' ',block,block,block,  ' ',block,  ' ',block,block,  ' ',block},
									{block,  ' ',  ' ',block,  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',block},
									{block,block,block,block,block,block,block,block,block,block,block,block,block,block,block} 
	};
	char c = 'a';

	placePlant(maze);
	placeWalker(maze);

	cout << "Do you want plants to grow? Enter y for yes\n";
	cin >> plantsCanGrow;

	while (c != 'x' && numOfPlants != 0)
	{
		drawMaze(maze, numRows, numCols);
		changePlants(maze);
		moveWalker(maze);
		cin >> c;
	}
	drawMaze(maze, numRows, numCols);
	if (numOfPlants == 0) {
		cout << "\n\nLife Simulation Complete\n\n";
		cout << "Enter any key to exit\n";
		cin >> c;
	}
}