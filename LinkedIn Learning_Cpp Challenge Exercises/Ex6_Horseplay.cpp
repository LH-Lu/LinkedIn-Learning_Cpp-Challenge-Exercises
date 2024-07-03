// Ex5: Recursive Factoral Sequence
// Write a program that takes in the chessboard location of a knight chess piece and prints the possible locations the knight can move to
// Assume:
//  The Knight chess piece is the only chess piece on the chessboard
// Note:
//  Knight can only move 2 squares horizontally + 1 square vertically OR 2 squares vertically + 1 sqaure horizontally --> Therefore, there are a maximum of 8 possible locations the Knight can move to
//  Chessboard grid layout is rows 1 - 8 (bottom to top) and A - H (left to right)

#include"CommonHeader.h"
#include"ExHeader.h"

void KnightLocationInput(char KnightLocation[], const int KnightLocationStrLen);
bool KnightLocationValidator(char KnightLocation[]);
int ChessBoardGridInterpreter(char KnightLocation[], const int RowSize);
void PossibleLocationCalculator(char ChessBoardGridArr[][8], int KnightLocationDigits, int VerticalMove, int HorizontalMove, const int RowSize, const int ColSize);

void HorsePlay() {

	// Step 0: Initialise variables
	const int RowSize = 8;
	const int ColSize = 8;

	int RowIdx, ColIdx;

	char ChessBoardGridArr[RowSize][ColSize];
	for (RowIdx = 0; RowIdx < RowSize; RowIdx++) {
		for (ColIdx = 0; ColIdx < ColSize; ColIdx++) {
			ChessBoardGridArr[RowIdx][ColIdx] = 'o';
		}
	}

	const int KnightLocationStrLen = 3;
	char KnightLocation[KnightLocationStrLen];
	int KnightLocationDigits; 

	// Step 1: Take in location of knight chess piece
	KnightLocationInput(KnightLocation, KnightLocationStrLen);
	KnightLocationDigits = ChessBoardGridInterpreter(KnightLocation, RowSize); // ArrRowNum * 10 + ArrColNum
	ChessBoardGridArr[KnightLocationDigits / 10][KnightLocationDigits % 10] = 'I'; // Ignore warning as the index will always be less than 8 due to KnightLocationValidator fn and ChessBoardGridInterpreter fn
	
	// Step 2: Calculate the possible locations the knight can move to
	PossibleLocationCalculator(ChessBoardGridArr, KnightLocationDigits, 2, 1, RowSize, ColSize);
	PossibleLocationCalculator(ChessBoardGridArr, KnightLocationDigits, 1, 2, RowSize, ColSize);

	// Step 3: Print result
	std::cout << "  A                    H" << std::endl;
	for (RowIdx = 0; RowIdx < RowSize; RowIdx++) {
		if (RowIdx == 0) {
			std::cout << "8 ";
		}
		else if (RowIdx == RowSize - 1) {
			std::cout << "1 ";
		}
		else {
			std::cout << "  ";
		}

		for (ColIdx = 0; ColIdx < ColSize; ColIdx++) {
			std::cout << ChessBoardGridArr[RowIdx][ColIdx] << "  ";
		}
		std::cout << std::endl << std::endl;
	}


}


void KnightLocationInput(char KnightLocation[], const int KnightLocationStrLen) {

	bool check1 = false;
	bool check2 = true;
	int idx = 0;
	char TempChar;

	while (check1 == false) {
		std::cout << "Enter location of knight: ";

		while (check2) {
			TempChar = std::getchar();

			if (TempChar == '\n' || TempChar == EOF) {
				check2 = false;
			}
			else if (idx < KnightLocationStrLen - 1) {
				KnightLocation[idx] = TempChar;
				idx++;
			}
		}
		KnightLocation[KnightLocationStrLen - 1] = '\0';

		check1 = KnightLocationValidator(KnightLocation);
		if (check1 == false) {
			std::cout << "Wrong location input!" << std::endl;
			// re-initialise to enter getchar block
			check2 = true; 
			idx = 0;
		}
		else {
			break;
		}
	}

}


bool KnightLocationValidator(char KnightLocation[]) {

	// Check col input
	if (!isalpha(KnightLocation[0])) {
		return false;
	}
	KnightLocation[0] = (char)std::toupper(KnightLocation[0]); // make upper case. Note need to type cast std::toupper as it returns an int value

	if (int(KnightLocation[0]) < 65 || int(KnightLocation[0]) > 72) { // compare through ASCII Dec values A through H is 65 to 72 inclusive
		return false;
	}

	// Check row input
	if (!isdigit(KnightLocation[1])) {
		return false;
	}

	if (int(KnightLocation[1]) < 49 || int(KnightLocation[1]) > 56) { // compare through ASCII Dec values 1 through 8 is 49 to 56 inclusive
		return false;
	}

	// Input successfully validated
	return true;
}


int ChessBoardGridInterpreter(char KnightLocation[], const int RowSize) {

	// Interpret col input --> program mtx coordinates (ASCII Dec values A through H is 65 to 72 inclusive)
	int ColCoord = int(KnightLocation[0]) - 65;

	// Interpret row input --> program mtx coordinates (ASCII Dec values 1 through 8 is 49 to 56 inclusive)
	int RowCoord = int(KnightLocation[1]) - 49;
	RowCoord = (RowSize - 1) - RowCoord;

	return (RowCoord * 10 + ColCoord);
}


void PossibleLocationCalculator(char ChessBoardGridArr[][8], int KnightLocationDigits, int VerticalMove, int HorizontalMove, const int RowSize, const int ColSize) {

	int KnightRow = KnightLocationDigits / 10;
	int KnightCol = KnightLocationDigits % 10;

	bool UpCheck = false;
	bool DownCheck = false;
	bool LeftCheck = false;
	bool RightCheck = false;
	
	// Move up vertically check
	if ((KnightRow - VerticalMove) >= 0) {
		UpCheck = true;
	}

	// Move down vertically check
	if ((KnightRow + VerticalMove) <= (RowSize - 1)) {
		DownCheck = true;
	}

	// Move left horizontally check
	if ((KnightCol - HorizontalMove) >= 0) {
		LeftCheck = true;
	}

	// Move right horizontally check
	if ((KnightCol + HorizontalMove) <= (ColSize - 1)) {
		RightCheck = true;
	}

	// Make possible movements
	if (UpCheck == true) {
		if (LeftCheck == true) {
			ChessBoardGridArr[KnightRow - VerticalMove][KnightCol - HorizontalMove] = 'x';
		}
		if (RightCheck == true) {
			ChessBoardGridArr[KnightRow - VerticalMove][KnightCol + HorizontalMove] = 'x';
		}
	}

	if (DownCheck == true) {
		if (LeftCheck == true) {
			ChessBoardGridArr[KnightRow + VerticalMove][KnightCol - HorizontalMove] = 'x';
		}
		if (RightCheck == true) {
			ChessBoardGridArr[KnightRow + VerticalMove][KnightCol + HorizontalMove] = 'x';
		}
	}

}