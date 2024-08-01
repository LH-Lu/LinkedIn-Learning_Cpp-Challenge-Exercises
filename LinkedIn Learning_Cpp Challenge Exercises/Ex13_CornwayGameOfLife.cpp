// Ex13: Cornway's Game of Life

// Create an application that runs Cornway's Game of Life
// Do for a 10 x 10 grid that wraps in all directions (i.e top and bottom most squares are neighbours, left and right most squares are neightbours)

// Rules (in current iteration):
//	Each cell has 8 neighbours (top, bottom and diagonals and all directions)
//	Cell dies if number of neighbours < 2
//	Cell lives to next iteration if number of neighbours == 2 or 3
//	Cell dies if number of neighbours > 3
//	Cell revives if number of neighbours == 3

#include "CommonHeader.h"
#include"ExHeader.h"
#include<chrono> // to pause program for defined number of seconds
#include<thread> // to pause program for defined number of seconds
#define MAXROW 10
#define MAXCOL 10

void PrintGrid(char Game[][MAXCOL]) {
	int RowIdx, ColIdx;

	for (RowIdx = 0; RowIdx < MAXROW; RowIdx++) {
		for (ColIdx = 0; ColIdx < MAXCOL; ColIdx++) {
			std::cout << Game[RowIdx][ColIdx] << " ";
		}
		std::cout << std::endl;
	}
}

// Seed the grid based on user input (with some standard shapes available)
void SeedGame(char Game[][MAXCOL], const char& alive) {
	
	bool check1 = false;
	int ShapeChoice, Quadrant, RowIdx, ColIdx;
	const int ShapeMaxRow = 5;
	const int ShapeMaxCol = 5;
	char Shape[ShapeMaxRow][ShapeMaxCol];

	while (!check1) {
		// user choose shape --> choose quadrant to place the shape in main game grid
		std::cout << "Standard seed shapes" << std::endl;
		std::cout << "1 - Glider" << std::endl;
		std::cout << "2 - Blinker" << std::endl;
		std::cout << "0 - RETURN TO START RUN" << std::endl;
		std::cout << "Choice (1 - 2): ";
		std::cin >> ShapeChoice;
		std::cout << std::endl;

		if (ShapeChoice == 0) { return; }

		std::cout << "Choose location to place the shape" << std::endl;
		std::cout << "1 - Top Left" << std::endl;
		std::cout << "2 - Top Right" << std::endl;
		std::cout << "3 - Bottom Left" << std::endl;
		std::cout << "4 - Bottom Right" << std::endl;
		std::cout << "Choice (1 - 4): ";
		std::cin >> Quadrant;
		std::cout << std::endl;

		// initialise Shape working copy
		for (RowIdx = 0; RowIdx < ShapeMaxRow; RowIdx++) {
			for (ColIdx = 0; ColIdx < ShapeMaxCol; ColIdx++) {
				Shape[RowIdx][ColIdx] = ' ';
			}
		}

		// get working shape
		switch (ShapeChoice) {
		case 1: // glider
			Shape[1][1] = alive;
			Shape[2][2] = alive;
			Shape[3][0] = alive;
			Shape[3][1] = alive;
			Shape[3][2] = alive;
			break;

		case 2: // blinker
			Shape[3][1] = alive;
			Shape[3][2] = alive;
			Shape[3][3] = alive;
			break;

		default:
			std::cout << "Entered wrong shape number input!" << std::endl;
			continue;
		}

		// Tranfer shapes from a working 5 by 5 grid to the main 10 by 10 game grid in the appropiate quadrant
		if (Quadrant < 1 || Quadrant > 4) {
			std::cout << "Entered wrong quadrant input!" << std::endl;
			continue;
		}
		for (RowIdx = 0; RowIdx < ShapeMaxRow; RowIdx++) {
			for (ColIdx = 0; ColIdx < ShapeMaxCol; ColIdx++) {
				switch (Quadrant) {
				case 1: // top left
					Game[RowIdx][ColIdx] = Shape[RowIdx][ColIdx];
					break;

				case 2: // top right
					Game[RowIdx][ColIdx + ShapeMaxCol] = Shape[RowIdx][ColIdx];
					break;

				case 3: // bottom left
					Game[RowIdx + ShapeMaxRow][ColIdx] = Shape[RowIdx][ColIdx];
					break;

				case 4: // bottom right
					Game[RowIdx + ShapeMaxRow][ColIdx + ShapeMaxCol] = Shape[RowIdx][ColIdx];
					break;
				}
			}
		}
		
		PrintGrid(Game);
	}
	
}

void CopyGameGrid(char Original[][MAXCOL], char Copy[][MAXCOL]) {
	int RowIdx, ColIdx;
	for (RowIdx = 0; RowIdx < MAXROW; RowIdx++) {
		for (ColIdx = 0; ColIdx < MAXCOL; ColIdx++) {
			Copy[RowIdx][ColIdx] = Original[RowIdx][ColIdx];
		}
	}
}

int CheckNeighboursNum(const char Game[][MAXCOL], const char& alive, const int& GameRowIdx, const int& GameColIdx) {
	int RowIdx, ColIdx;
	
	int count = 0;

	int UpperRow = GameRowIdx - 1;
	int LowerRow = GameRowIdx + 1;
	int LeftCol = GameColIdx - 1;
	int RightCol = GameColIdx + 1;

	// check for limits
	if (UpperRow < 0) {
		UpperRow = MAXROW - 1;
	}
	if (LowerRow >= MAXROW) {
		LowerRow = 0;
	}

	if (LeftCol < 0) {
		LeftCol = MAXCOL - 1;
	}
	if (RightCol >= MAXCOL) {
		RightCol = 0;
	}

	// count neighbours above
	if (Game[UpperRow][LeftCol] == alive) { count++; }
	if (Game[UpperRow][GameColIdx] == alive) { count++; }
	if (Game[UpperRow][RightCol] == alive) { count++; }

	// count neighbours below
	if (Game[LowerRow][LeftCol] == alive) { count++; }
	if (Game[LowerRow][GameColIdx] == alive) { count++; }
	if (Game[LowerRow][RightCol] == alive) { count++; }

	// count neighbours beside
	if (Game[GameRowIdx][LeftCol] == alive) { count++; }
	if (Game[GameRowIdx][RightCol] == alive) { count++; }

	return count;

}

// Apply game rules to determine the state of the cell for next iteration
void CellState(char& cell, const int& NumOfNeighbours, const char& alive, const char& died) {
	// Rules (in current iteration):
	//	Each cell has 8 neighbours (top, bottom and diagonals and all directions)
	//	Cell dies if number of neighbours < 2
	//	Cell lives to next iteration if number of neighbours == 2 or 3
	//	Cell dies if number of neighbours > 3
	//	Cell revives if number of neighbours == 3

	if (NumOfNeighbours < 2) {
		cell = died;
		return;
	}

	if (cell == alive && (NumOfNeighbours == 2 || NumOfNeighbours == 3)) {
		cell = alive;
		return;
	}

	if (NumOfNeighbours > 3) {
		cell = died;
		return;
	}

	if (cell == died && NumOfNeighbours == 3) {
		cell = alive;
		return;
	}
}


void Main_CornwayGameOfLife() {

	// Step 0: Initialise global varaibles
	char GameNow[MAXROW][MAXCOL];
	char GameNextItr[MAXROW][MAXCOL];
	const char alive = 'X';
	const char died = ' ';

	char NextItrChar;

	int RowIdx, ColIdx;
	for (RowIdx = 0; RowIdx < MAXROW; RowIdx++) {
		for (ColIdx = 0; ColIdx < MAXCOL; ColIdx++) {
			GameNow[RowIdx][ColIdx] = died;
			GameNextItr[RowIdx][ColIdx] = died;
		}
	}

	// Step 1: Input seed + ask for number of iterations + print grid
	int TotalIteration;
	std::cout << "How many iterations to run? Enter -1 for unlimited iterations with manual step." << std::endl;
	std::cout << "Number of iterations: ";
	std::cin >> TotalIteration;
	std::cout << std::endl;

	SeedGame(GameNow, alive);

	std::cout << "Start of simulation. Iteration #0" << std::endl;
	PrintGrid(GameNow);
	std::cout << std::endl << std::endl;
	std::cout << "Press ENTER to start." << std::endl;
	NextItrChar = std::getchar();

	// Step 2: Iterate through the generations and print grid. Ensure a way to exit loop
	int Iteration = 1;
	int NumOfNeighbours;

	while (NextItrChar == '\n') {
		system("cls");
		// copy current game state to working copy
		CopyGameGrid(GameNow, GameNextItr);

		for (RowIdx = 0; RowIdx < MAXROW; RowIdx++) {
			for (ColIdx = 0; ColIdx < MAXCOL; ColIdx++) {
				// check number of neighbours next to cell
				NumOfNeighbours = CheckNeighboursNum(GameNow, alive, RowIdx, ColIdx);

				// change new state of cell base on game rules
				CellState(GameNextItr[RowIdx][ColIdx], NumOfNeighbours, alive, died);
			}
		}

		// update original game state with working copy
		CopyGameGrid(GameNextItr, GameNow);

		// Print
		std::cout << "Iteration #" << Iteration << std::endl;
		Iteration++;
		PrintGrid(GameNow);
		std::cout << std::endl << std::endl;

		if (TotalIteration != -1) {
			if (Iteration > TotalIteration) {
				NextItrChar == 'E';
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(200)); // pause for 0.2s
		}
		else {
			std::cout << "Press ENTER to proceed to the next itreation. Press 'e' to end game." << std::endl;
			NextItrChar = std::getchar();
			if (NextItrChar == 'E' || NextItrChar == 'e') {
				break;
			}
		}
	}

}