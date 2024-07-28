// Ex10: Tic Tac Toe Game

// Write a single player console game where the computer plays tic tac toe against the user

#include "CommonHeader.h"
#include "ExHeader.h"
#include <cstdlib> // to get rand() function to generate random numbers
#define MAXGRID 3

// List of functions: print game board with locations. computer decisions. check win/lost/tie
enum PlayerStatus {
	Ongoing = 0, Tie, Win, Lose
};

class Player {

public:
	char Symbol;
	PlayerStatus Status = Ongoing;

public:
	// Get player input on where to place their symbol
	void Play(char GameBoard[][MAXGRID], const int& RowMax, const int& ColMax) {
		int UserInputRow, UserInputCol;
		bool check1 = false;

		while (!check1) {
			// get input
			std::cout << "Enter Row number: ";
			std::cin >> UserInputRow;
			UserInputRow--;

			std::cout << "Enter Column number: ";
			std::cin >> UserInputCol;
			UserInputCol--;

			// validate input
			if (UserInputRow < 0 || UserInputRow >= RowMax || UserInputCol < 0 || UserInputCol >= ColMax) {
				std::cout << "Wrong value entered! Value 1 ~ 3 only!" << std::endl;
				continue;
			}
			if (GameBoard[UserInputRow][UserInputCol] != ' ') {
				std::cout << "Space has been filled! Choose another spot." << std::endl;
				continue;
			}

			// change gameboard status
			GameBoard[UserInputRow][UserInputCol] = Symbol;
			check1 = true;
		}
		std::cout << std::endl;
	}

	// Check status of the game by checking if player who recently played has won --> update status of both players
	void CheckGameStatus(char GameBoard[][MAXGRID], const int& RowMax, const int& ColMax, PlayerStatus& OpponentStatus) {
		int RowIdx, ColIdx;

		// check row-wise (entire row filled by 1 player)
		for (RowIdx = 0; RowIdx < RowMax; RowIdx++) {
			if (GameBoard[RowIdx][0] == Symbol && GameBoard[RowIdx][1] == GameBoard[RowIdx][0] && GameBoard[RowIdx][2] == GameBoard[RowIdx][0]) {
				Status = Win;
				OpponentStatus = Lose;
				return;
			}
		}

		// check col-wise (entire col filled by 1 player)
		for (ColIdx = 0; ColIdx < ColMax; ColIdx++) {
			if (GameBoard[0][ColIdx] == Symbol && GameBoard[1][ColIdx] == GameBoard[0][ColIdx] && GameBoard[2][ColIdx] == GameBoard[0][ColIdx]) {
				Status = Win;
				OpponentStatus = Lose;
				return;
			}
		}

		// check diagonal (entire diagonal filled by 1 player)
		if (GameBoard[0][0] == Symbol && GameBoard[1][1] == GameBoard[0][0] && GameBoard[2][2] == GameBoard[0][0]) {
			Status = Win;
			OpponentStatus = Lose;
			return;
		}
		if (GameBoard[0][2] == Symbol && GameBoard[1][1] == GameBoard[0][2] && GameBoard[2][0] == GameBoard[0][2]) {
			Status = Win;
			OpponentStatus = Lose;
			return;
		}

		// check tie (all spaces filled)
		for (RowIdx = 0; RowIdx < RowMax; RowIdx++) {
			for (ColIdx = 0; ColIdx < ColMax; ColIdx++) {
				if (GameBoard[RowIdx][ColIdx] == ' ') {
					Status = Ongoing;
					OpponentStatus = Ongoing;
					return;
				}
			}
		}
		Status = Tie;
		OpponentStatus = Tie;
	}

	// Prints game status of player
	std::string PrintPlayerStatus() {
		switch (Status) {
		case Ongoing:
			return "ONGOING";
			break;

		case Tie:
			return "TIE";
			break;

		case Win:
			return "WIN";
			break;

		case Lose:
			return "LOSE";
			break;
		}
	}
};

class AIPlayer : public Player {
public:
	// Determines where the computer places its symbol
	void Play(char GameBoard[][MAXGRID], const int& RowMax, const int& ColMax) {
		
		int RowIdx, ColIdx;
		bool check = false;
		
		// Fill a place with only 1 space left (row-wise)
		for (RowIdx = 0; RowIdx < RowMax; RowIdx++) {
			check = LocationDeterminer(GameBoard[RowIdx], RowMax, 1, Symbol);

			if (check == true) {
				return;
			}
		}

		// Fill a place with only 1 space left (col-wise)
		char tempArr[MAXGRID];

		for (ColIdx = 0; ColIdx < ColMax; ColIdx++) {
			for (RowIdx = 0; RowIdx < RowMax; RowIdx++) {
				tempArr[RowIdx] = GameBoard[RowIdx][ColIdx];
			}
			check = LocationDeterminer(tempArr, ColMax, 1, Symbol);

			if (check == true) {
				for (RowIdx = 0; RowIdx < RowMax; RowIdx++) {
					GameBoard[RowIdx][ColIdx] = tempArr[RowIdx];
				}
				return;
			}
		}

		// Fill a place with only 1 space left (diag-wise)
		int idx;
		for (idx = 0; idx < MAXGRID; idx++) {
			tempArr[idx] = GameBoard[idx][idx];
		}
		check = LocationDeterminer(tempArr, MAXGRID, 1, Symbol);
		if (check == true) {
			for (idx = 0; idx < MAXGRID; idx++) {
				GameBoard[idx][idx] = tempArr[idx];
			}
			return;
		}

		for (idx = 0; idx < MAXGRID; idx++) {
			tempArr[idx] = GameBoard[MAXGRID - idx - 1][idx];
		}
		check = LocationDeterminer(tempArr, MAXGRID, 1, Symbol);
		if (check == true) {
			for (idx = 0; idx < MAXGRID; idx++) {
				GameBoard[MAXGRID - idx - 1][idx] = tempArr[idx];
			}
			return;
		}

		// Fill a place if 2 or more spaces left (col or row-wise) --> do it randomly
		bool check1 = false;
		while (!check1) {
			// generate a random number between 0 and 3 (exclusive)
			RowIdx = rand() % 3;
			ColIdx = rand() % 3;
			if (RowIdx < 0 || RowIdx >= RowMax || ColIdx < 0 || ColIdx >= ColMax) {
				continue;
			}

			// check if placed is filled
			if (GameBoard[RowIdx][ColIdx] != ' ') {
				continue;
			}

			// place symbol
			GameBoard[RowIdx][ColIdx] = Symbol;
			check1 = true;
		}
		
	}

private:
	bool LocationDeterminer(char GameBoard[], int ArrMax, int EmptySpaces, const char& PlayerSymb) {
		int idx, countBlank;
		countBlank = 0;

		for (idx = 0; idx < ArrMax; idx++) {
			if (GameBoard[idx] == ' ') {
				countBlank++;
			}
		}

		if (countBlank != EmptySpaces) {
			return false;
		}

		for (idx = 0; idx < ArrMax; idx++) {
			if (GameBoard[idx] == ' ') {
				GameBoard[idx] = PlayerSymb;
				break;
			}
		}
		return true;
	}
};

void AssignSymb(Player& Player1, AIPlayer& Computer, const char& x, const char& o);
void PrintGame(char GameBoard[][MAXGRID], const int& RowMax, const int& ColMax, Player& Player1, AIPlayer& Computer);

void Main_TicTacToe() {

	// Step 0: Initialise global variables
	const int RowMax = MAXGRID;
	const int ColMax = MAXGRID;

	const char x = 'x';
	const char o = 'o';

	Player Player1;
	AIPlayer Computer;

	char GameBoard[RowMax][ColMax];

	// Step 1: Ask user for choice of symbol ('x' goes first) --> assign computer the other symbol
	AssignSymb(Player1, Computer, x, o);
	system("cls");

	// Step 2: Initialise GameGrid
	int RowIdx, ColIdx;

	for (RowIdx = 0; RowIdx < RowMax; RowIdx++) {
		for (ColIdx = 0; ColIdx < ColMax; ColIdx++) {
			GameBoard[RowIdx][ColIdx] = ' ';
		}
	}

	// Step 3: Print game board + relevant info --> ask input for 'x' --> print game board with 'x' location --> ask input for 'o' --> print game board with 'o' location --> 
	// check if game win/lost/tie --> yes, end game --> no, clear console & repeat process
	bool check1 = false;

	while (!check1) {
		

		if (Player1.Symbol == x) {
			PrintGame(GameBoard, RowMax, ColMax, Player1, Computer);
			
			Player1.Play(GameBoard, RowMax, ColMax);
			system("cls");
			Player1.CheckGameStatus(GameBoard, RowMax, ColMax, Computer.Status);
			PrintGame(GameBoard, RowMax, ColMax, Player1, Computer);
			if (Player1.Status != Ongoing) {
				check1 = true;
				break;
			}
			system("cls");

			Computer.Play(GameBoard, RowMax, ColMax);
			Computer.CheckGameStatus(GameBoard, RowMax, ColMax, Player1.Status);
			PrintGame(GameBoard, RowMax, ColMax, Player1, Computer);
			if (Computer.Status != Ongoing) {
				check1 = true;
				break;
			}
			system("cls");

		}
		else if (Computer.Symbol == x) {

			Computer.Play(GameBoard, RowMax, ColMax);
			Computer.CheckGameStatus(GameBoard, RowMax, ColMax, Player1.Status);
			PrintGame(GameBoard, RowMax, ColMax, Player1, Computer);
			if (Computer.Status != Ongoing) {
				check1 = true;
				break;
			}

			Player1.Play(GameBoard, RowMax, ColMax);
			system("cls");
			Player1.CheckGameStatus(GameBoard, RowMax, ColMax, Computer.Status);
			PrintGame(GameBoard, RowMax, ColMax, Player1, Computer);
			if (Player1.Status != Ongoing) {
				check1 = true;
				break;
			}
			system("cls");

		}
	}



}

// Function gets user input on which symbol the user wants to play with
void AssignSymb(Player& Player1, AIPlayer& Computer, const char& x, const char& o) {
	bool check1 = false;
	char UserSymbTemp;

	while (!check1) {
		std::cout << "Choose your symbol. Note, 'x' goes first (x/o): ";
		UserSymbTemp = std::getchar();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush buffer

		if (UserSymbTemp == 'x' || UserSymbTemp == 'o') {
			check1 = true;
		}
		else {
			std::cout << "Wrong character entered! Enter either 'x' or 'o' only!" << std::endl;
		}
	}

	Player1.Symbol = UserSymbTemp;

	switch (Player1.Symbol) {
	case 'x':
		Computer.Symbol = o;
		break;
		
	case 'o':
		Computer.Symbol = x;
		break;
	}
}

// Function prints game info and the game board
void PrintGame(char GameBoard[][MAXGRID], const int& RowMax, const int& ColMax, Player& Player1, AIPlayer& Computer) {

	// Print game info
	std::cout << "Player: " << Player1.Symbol << " (" << Player1.PrintPlayerStatus() << ")" << std::endl;
	std::cout << "Computer: " << Computer.Symbol << " (" << Computer.PrintPlayerStatus() << ")" << std::endl;
	std::cout << std::endl;

	// Print game board
	int RowIdx, ColIdx;

	std::cout << "   1   2   3" << std::endl;

	for (RowIdx = 0; RowIdx < RowMax; RowIdx++) {
		std::cout << RowIdx + 1;
		for (ColIdx = 0; ColIdx < ColMax; ColIdx++) {
			std::cout << "| " << GameBoard[RowIdx][ColIdx] << " ";
		}
		
		std::cout << std::endl;
		if (RowIdx == 2) {
			break;
		}
		std::cout << "_+___+___+___" << std::endl;
	}

	std::cout << std::endl;
}
