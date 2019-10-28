#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const int numRows = 25;//Must be odd number, >=5
const int numCols = 65;//Must be odd number, >=5
int numOfPlants = 20;
int numOfWalkers = 55;
char plantsCanGrow = 'a';
char block = 219;
char ground = ' ';

void drawMaze(char mz[numRows][numCols]) {

	for (int row = 0; row < numRows; row++)
	{
		cout << "	";
		for (int col = 0; col < numCols; col++)
		{
			if (mz[row][col] >= 'a' && mz[row][col] <= 'y') {
				SetConsoleTextAttribute(hConsole, 10);
				cout << mz[row][col];
				SetConsoleTextAttribute(hConsole, 15);
			}
			else if (mz[row][col] == '2') {
				SetConsoleTextAttribute(hConsole, 6);
				cout << mz[row][col];
				SetConsoleTextAttribute(hConsole, 15);
			}
			else {
				SetConsoleTextAttribute(hConsole, 8);
				cout << mz[row][col];
				SetConsoleTextAttribute(hConsole, 15);
			}
		}
		cout << endl;
	}
}

//Used to generate the basic cell structure that genMaze() relies on
void genBaseMaze(char mz[numRows][numCols]) {
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			mz[row][col] = block;
		}
	}

	for (int row = 3; row < numRows - 2; row += 2) {
		for (int col = 3; col < numCols - 2; col += 2) {
			mz[row][col] = ground;
		}
	}
}

void copyArr(char mzO[numRows][numCols], char mz[numRows][numCols]) {
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			mz[row][col] = mzO[row][col];
		}
	}
}

void genMaze(char mz[numRows][numCols]) {
	int chance = 0;
	//The below variable can be raised or lowered to increase or decrease the
	//amount of walls in the maze. A very low number increases chance of unreachable areas
	int chanceCheckNum = 5;
	int colN = 3;

	for (int row = 2; row < numRows - 2; row++) {

		for (int col = colN; col < numCols - colN; col += 2) {
			chance = rand() % 10;
			if (chance < chanceCheckNum) mz[row][col] = ground;
		}
		if (colN == 3) {
			colN = 2;
		}
		else colN = 3;
	}
	//Draw edge maze ground
	for (int col = 1; col < numCols - 1; col++) {
			mz[1][col] = ground;
			mz[numRows - 2][col] = ground;
	}
	for (int row = 1; row < numRows - 1; row++) {
			mz[row][1] = ground;
			mz[row][numCols - 2] = ground;
	}
	//Search for lone cells and rare isolated 3 cell areas, and connect to other cells
	//The large compound if was necessary to catch the 3 cell areas that were unconnected
	for (int row = 3; row < numRows - 3; row++) {
		for (int col = 3; col < numCols - 3; col++) {
			if (mz[row][col] == ground && (mz[row - 1][col] == block || mz[row - 3][col] == block) && (mz[row + 1][col] == block || mz[row + 3][col] == block) && (mz[row][col - 1] == block || mz[row][col - 3] == block) && (mz[row][col + 1] == block || mz[row][col + 3] == block)) {
				int rowOrCol = rand() % 2;
				//Creates an L shape that will break through to rest of maze
				//rowOrCol randomises direction of L
				if (rowOrCol == 0) {
					int rowC = rand() % 2;
					if (rowC == 0) {
						mz[row - 1][col] = ground; 
						mz[row - 2][col] = ground;
						mz[row - 2][col - 1] = ground;
						mz[row - 2][col - 2] = ground;
					}
					else {
						mz[row + 1][col] = ground;
						mz[row + 2][col] = ground;
						mz[row + 2][col + 1] = ground;
						mz[row + 2][col + 2] = ground;
					}
				}
				else {
					int colC = rand() % 2;
					if (colC == 0) {
						mz[row][col - 1] = ground;
						mz[row][col - 2] = ground;
						mz[row - 1][col - 2] = ground;
						mz[row - 2][col - 2] = ground;
					}
					else {
						mz[row][col + 1] = ground;
						mz[row][col + 2] = ground;
						mz[row + 1][col + 2] = ground;
						mz[row + 2][col + 2] = ground;
					}
				}
			}
		}
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
					mz[adjRow][adjCol] = '?';//Placeholder to avoid new plant being checked same turn
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
				plantReached = 0;
				canChange = 1;
				for (int checkRow = 1; checkRow < numCols-1; checkRow++) {

					if (checkRow == arrCol) {
						plantReached = 1;//Checking Plant has been reached in Row
					}
					if (checkRow == arrCol && canChange == 0) {
						break;//Plant sees Walker
					}
					else if (mz[arrRow][checkRow] == '2' && plantReached == 0) {
						canChange = 0;//Plant might see walker
					}
					else if (mz[arrRow][checkRow] == block && plantReached == 0) {
						canChange = 1;//Plant might not see walker
					}
					else if (mz[arrRow][checkRow] == '2' && plantReached == 1) {
						canChange = 0;
						break;//Plant sees Walker
					}
					else if (mz[arrRow][checkRow] == block && plantReached == 1 && canChange == 1) {
						break;//Plant can't see Walker in Row
					}
				}
				//If canChange ==0, no need for second loop
				if (canChange == 1) {
					plantReached = 0;
					for (int checkCol = 1; checkCol < numRows-1; checkCol++) {

						if (checkCol == arrRow) {
							plantReached = 1;
						}
						if (checkCol == arrRow && canChange == 0) {
							break;//Plant sees Walker
						}
						else if (mz[checkCol][arrCol] == '2' && plantReached == 0) {
							canChange = 0;
						}
						else if (mz[checkCol][arrCol] == block && plantReached == 0) {
							canChange = 1;
						}
						else if (mz[checkCol][arrCol] == '2' && plantReached == 1) {
							canChange = 0;
							break;//Plant sees Walker
						}
						else if (mz[checkCol][arrCol] == block && plantReached == 1 && canChange == 1) {
							break;//Plant can't see Walker in Col
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
					//Plant mutation dealt with here
					if (plantsCanGrow == 'y') {
						plantsGrow(mz, arrRow, arrCol);
					}
				}
			}
		}
	}
	//Change placeholders to plants
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
					if (mz[row][col] != ' ') {//Tidier than defining range a->y
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
	
	char mazeO[numRows][numCols] = {};
	char maze[numRows][numCols] = {};

	genBaseMaze(mazeO);
	copyArr(mazeO, maze);
	genMaze(maze);
	drawMaze(maze);

	char cont = 'a';
	char keepMaze = 'n';
	cout << "\n	Are you happy with the maze? Enter y for yes\n	";
	cin >> keepMaze;

	while (keepMaze != 'y') {
		copyArr(mazeO, maze);
		genMaze(maze);
		drawMaze(maze);
		cout << "\n	Are you happy with the maze? Enter y for yes\n	";
		cin >> keepMaze;
	}

	placePlant(maze);
	placeWalker(maze);

	cout << "\n	Do you want plants to grow? Enter y for yes\n	";
	cin >> plantsCanGrow;

	while (cont != 'x' && numOfPlants != 0)
	{
		drawMaze(maze);
		changePlants(maze);
		moveWalker(maze);
		cin >> cont;
	}
	drawMaze(maze);
	if (numOfPlants == 0) {
		SetConsoleTextAttribute(hConsole, 12);
		cout << "\n\n	Life Simulation Complete\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		cout << "	Enter any key to exit\n	";
		cin >> cont;
	}
}