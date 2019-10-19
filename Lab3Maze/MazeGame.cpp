#include <iostream>
#include <ctime>


using namespace std;

const int mazeSize = 15;
int numOfPlants = 10;
int numOfWalkers = 15;
char plantsCanGrow = 'a';
char block = 219;

void drawMaze(char mz[mazeSize][mazeSize], int numRows, int numCols)
{
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

void placePlant(char mz[mazeSize][mazeSize], int nOP) {
	int count = 0;
	srand(time(NULL));
	while (count < nOP) {
		int i = rand() % (mazeSize - 1) + 1;
		int j = rand() % (mazeSize - 1) + 1;

		if (mz[i][j] == ' ') {
			mz[i][j] = 'y';
			count++;
		}
	}
}

void placeWalker(char mz[mazeSize][mazeSize]) {
	int count = 0;
	srand(time(NULL));
	while (count < numOfWalkers) {
		int i = rand() % (mazeSize - 1) + 1;
		int j = rand() % (mazeSize - 1) + 1;

		if (mz[i][j] == ' ') {
			mz[i][j] = '2';
			count++;
		}
	}
}

void plantsGrow(char mz[mazeSize][mazeSize], int aR, int aC) {
	for (int adjRow = aR - 1; adjRow <= aR + 1; adjRow++) {
		for (int adjCol = aC - 1; adjCol <= aC + 1; adjCol++) {
			//Only move to position with ' '
			if (mz[adjRow][adjCol] == ' ') {
				int willGrow = rand() % 10 + 1;
				if (willGrow == 10) {
					mz[adjRow][adjCol] = '?';
					numOfPlants++;
				}
			}
		}
	}
}

void changePlants(char mz[mazeSize][mazeSize]) {
	int canChange = 1;
	int exitLoop = 0;

	for (int arrRow = 1; arrRow < mazeSize - 1; arrRow++) {
		for (int arrCol = 1; arrCol < mazeSize - 1; arrCol++) {
			if (mz[arrRow][arrCol] >= 'a' && mz[arrRow][arrCol] <= 'y') {
				canChange = 1;
				exitLoop = 0;
				for (int checkRow = 1; checkRow < 9; checkRow++) {

					if (checkRow == arrRow) {
						exitLoop = 1;
					}
					if (checkRow == arrRow && canChange == 0) {
						break;
					}
					else if (mz[checkRow][arrCol] == '2' && exitLoop == 0) {
						canChange = 0;
					}
					else if (mz[checkRow][arrCol] == block && exitLoop == 0) {
						canChange = 1;
					}
					else if (mz[checkRow][arrCol] == '2' && exitLoop == 1) {
						canChange = 0;
						break;
					}
					else if (mz[checkRow][arrCol] == block && exitLoop == 1 && canChange == 1) {
						break;
					}

				}
				if (canChange == 1) {
					exitLoop = 0;
					for (int checkCol = 1; checkCol < 9; checkCol++) {

						if (checkCol == arrCol) {
							exitLoop = 1;
						}
						if (checkCol == arrCol && canChange == 0) {
							break;
						}
						else if (mz[arrRow][checkCol] == '2' && exitLoop == 0) {
							canChange = 0;
						}
						else if (mz[arrRow][checkCol] == block && exitLoop == 0) {
							canChange = 1;
						}
						else if (mz[arrRow][checkCol] == '2' && exitLoop == 1) {
							canChange = 0;
							break;
						}
						else if (mz[arrRow][checkCol] == block && exitLoop == 1 && canChange == 1) {
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
	for (int arrRow = 1; arrRow < mazeSize - 1; arrRow++) {
		for (int arrCol = 1; arrCol < mazeSize - 1; arrCol++) {
			if (mz[arrRow][arrCol] == '?') {
				mz[arrRow][arrCol] = 'y';
			}
		}
	}
}

void moveWalker(char mz[mazeSize][mazeSize]) {
	for (int arrRow = 1; arrRow < mazeSize - 1; arrRow++) {
		for (int arrCol = 1; arrCol < mazeSize - 1; arrCol++) {
			if (mz[arrRow][arrCol] == '2') {
				int findSpace = 0;
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
				if (findSpace == 1) {
					int temp = arrRow - 1;
					int temp2 = arrCol - 1;
					srand(time(NULL));
					int row = rand() % 3 + (arrRow - 1);
					int col = rand() % 3 + (arrCol - 1);
					while (mz[row][col] == block || mz[row][col] == '2' || mz[row][col] == 'X') {
						row = rand() % 3 + (arrRow - 1);
						col = rand() % 3 + (arrCol - 1);
					}
					if (mz[row][col] != ' ') {
						numOfPlants--;
					}
					mz[row][col] = 'X';
					mz[arrRow][arrCol] = ' ';
				}
			}
		}
	}
	//Change placeholders to 2's
	for (int arrRow = 1; arrRow < mazeSize; arrRow++) {
		for (int arrCol = 1; arrCol < mazeSize; arrCol++) {
			if (mz[arrRow][arrCol] == 'X') {
				mz[arrRow][arrCol] = '2';
			}
		}
	}
}

/*void moveWalker(char mz[mazeSize][mazeSize]) {
	//Search array for 2's
	for (int arrRow = 1; arrRow < mazeSize-1; arrRow++) {
		for (int arrCol = 1; arrCol < mazeSize-1; arrCol++) {
			int breakSwitch = 1;//used to break out of nested loops in Switch
			if (mz[arrRow][arrCol] == '2') {
				srand(time(NULL));
				int move = rand() % 8 + 1;

				switch (move) {
					case 1: {
						for (int adjRow = arrRow - 1; adjRow <= arrRow + 1; adjRow++) {
							for (int adjCol = arrCol - 1; adjCol <= arrCol + 1; adjCol++) {
								//Only move to position with ' ' or a-y
								if (mz[adjRow][adjCol] != block && mz[adjRow][adjCol] != '2' && mz[adjRow][adjCol] != 'X') {
									//If position moved to is a plant
									if (mz[adjRow][adjCol] != ' ') {
										numOfPlants--;
									}
									mz[adjRow][adjCol] = 'X';//Placeholder used to avoid extra movements per turn
									mz[arrRow][arrCol] = ' ';
									breakSwitch = 0;
									break;
								}
							}
							if (breakSwitch == 0) {
								break;
							}
						}
						break;
					}
					case 2: {
						for (int adjCol = arrCol - 1; adjCol <= arrCol + 1; adjCol++) {
							for (int adjRow = arrRow - 1; adjRow <= arrRow + 1; adjRow++) {
								if (mz[adjRow][adjCol] != block && mz[adjRow][adjCol] != '2' && mz[adjRow][adjCol] != 'X') {
									if (mz[adjRow][adjCol] != ' ') {
										numOfPlants--;
									}
									mz[adjRow][adjCol] = 'X';
									mz[arrRow][arrCol] = ' ';
									breakSwitch = 0;
									break;
								}
							}
							if (breakSwitch == 0) {
								break;
							}
						}
						break;
					}
					case 3: {
						for (int adjRow = arrRow + 1; adjRow >= arrRow - 1; adjRow--) {
							for (int adjCol = arrCol - 1; adjCol <= arrCol + 1; adjCol++) {
								if (mz[adjRow][adjCol] != block && mz[adjRow][adjCol] != '2' && mz[adjRow][adjCol] != 'X') {
									if (mz[adjRow][adjCol] != ' ') {
										numOfPlants--;
									}
									mz[adjRow][adjCol] = 'X';
									mz[arrRow][arrCol] = ' ';
									breakSwitch = 0;
									break;
								}
							}
							if (breakSwitch == 0) {
								break;
							}
						}
						break;
					}
					case 4: {
						for (int adjCol = arrCol - 1; adjCol <= arrCol + 1; adjCol++) {
							for (int adjRow = arrRow + 1; adjRow >= arrRow - 1; adjRow--) {
								if (mz[adjRow][adjCol] != block && mz[adjRow][adjCol] != '2' && mz[adjRow][adjCol] != 'X') {
									if (mz[adjRow][adjCol] != ' ') {
										numOfPlants--;
									}
									mz[adjRow][adjCol] = 'X';
									mz[arrRow][arrCol] = ' ';
									breakSwitch = 0;
									break;
								}
							}
							if (breakSwitch == 0) {
								break;
							}
						}
						break;
					}
					case 5: {
						for (int adjRow = arrRow + 1; adjRow >= arrRow - 1; adjRow--) {
							for (int adjCol = arrCol + 1; adjCol >= arrCol - 1; adjCol--) {
								if (mz[adjRow][adjCol] != block && mz[adjRow][adjCol] != '2' && mz[adjRow][adjCol] != 'X') {
									if (mz[adjRow][adjCol] != ' ') {
										numOfPlants--;
									}
									mz[adjRow][adjCol] = 'X';
									mz[arrRow][arrCol] = ' ';
									breakSwitch = 0;
									break;
								}
							}
							if (breakSwitch == 0) {
								break;
							}
						}
						break;
					}
					case 6: {
						for (int adjCol = arrCol + 1; adjCol >= arrCol - 1; adjCol--) {
							for (int adjRow = arrRow + 1; adjRow >= arrRow - 1; adjRow--) {
								if (mz[adjRow][adjCol] != block && mz[adjRow][adjCol] != '2' && mz[adjRow][adjCol] != 'X') {
									if (mz[adjRow][adjCol] != ' ') {
										numOfPlants--;
									}
									mz[adjRow][adjCol] = 'X';
									mz[arrRow][arrCol] = ' ';
									breakSwitch = 0;
									break;
								}
							}
							if (breakSwitch == 0) {
								break;
							}
						}
						break;
					}
					case 7: {
						for (int adjRow = arrRow - 1; adjRow <= arrRow + 1; adjRow++) {
							for (int adjCol = arrCol + 1; adjCol >= arrCol - 1; adjCol--) {
								if (mz[adjRow][adjCol] != block && mz[adjRow][adjCol] != '2' && mz[adjRow][adjCol] != 'X') {
									if (mz[adjRow][adjCol] != ' ') {
										numOfPlants--;
									}
									mz[adjRow][adjCol] = 'X';
									mz[arrRow][arrCol] = ' ';
									breakSwitch = 0;
									break;
								}
							}
							if (breakSwitch == 0) {
								break;
							}
						}
						break;
					}
					case 8: {
						for (int adjCol = arrCol + 1; adjCol >= arrCol - 1; adjCol--) {
							for (int adjRow = arrRow - 1; adjRow <= arrRow + 1; adjRow++) {
								if (mz[adjRow][adjCol] != block && mz[adjRow][adjCol] != '2' && mz[adjRow][adjCol] != 'X') {
									if (mz[adjRow][adjCol] != ' ') {
										numOfPlants--;
									}
									mz[adjRow][adjCol] = 'X';
									mz[arrRow][arrCol] = ' ';
									breakSwitch = 0;
									break;
								}
							}
							if (breakSwitch == 0) {
								break;
							}
						}
						break;
					}
					default:
						break;
				}
			}
		}
	}
	//Change placeholders to 2's
	for (int arrRow = 1; arrRow < mazeSize-1; arrRow++) {
		for (int arrCol = 1; arrCol < mazeSize-1; arrCol++) {
			if (mz[arrRow][arrCol] == 'X') {
				mz[arrRow][arrCol] = '2';
			}
		}
	}
}*/

int main()
{
	const int numRows = 15;
	const int numCols = 15;
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
									{block,  ' ',  ' ',block,  ' ',  ' ',  ' ',  ' ',  ' ',block,  ' ',  ' ',  ' ',  ' ',block},
									{block,block,block,block,block,block,block,block,block,block,block,block,block,block,block} };
	char c = 'a';

	placePlant(maze, numOfPlants);
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
		cout << "Life Simulation Complete";
	}

}