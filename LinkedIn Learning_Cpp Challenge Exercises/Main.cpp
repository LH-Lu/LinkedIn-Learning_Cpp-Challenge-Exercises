// This is the main function --> access to individual exercises

#include"CommonHeader.h"
#include"ExHeader.h"


int main() {

	int ExNumber = -1;

	std::cout << "Please enter Exercise Number: ";
	std::cin >> ExNumber;
	std::cout << std::endl;
	system("cls"); // clear screen. Avoid clrscr() method from <conio.h> as its non-std cpp lib
	std::cout << "*** EXERCISE NUMBER " << ExNumber << " ***" << std::endl << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush buffer


	switch (ExNumber) {
	case 1:
		PalindromeCheck();
		break;

	case 2:
		SortArray();
		break;

	case 3:
		FizzBuzz();
		break;

	case 4:
		BitonicSequence();
		break;

	case 5:
		RecursiveFactoralSeq();
		break;

	case 6:
		HorsePlay();
		break;

	case 7:
		ComplexNumbers();
		break;

	case 8:
		IPCheck();
		break;

	case 9:
		debugCode();
		break;

	case 10:
		Main_TicTacToe();
		break;
	}

	std::cout << std::endl;
	std::cout << "*** PROGRAM ENDING ***" << std::endl;
	char endchar;
	endchar = std::getchar();

	return 0;
}