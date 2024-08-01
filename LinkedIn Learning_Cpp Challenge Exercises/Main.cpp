// This is the main function --> access to individual exercises

#include"CommonHeader.h"
#include"ExHeader.h"


int main() {

	int ExNumber = -1;

	std::cout << "Please enter Exercise Number (1 ~ 12): ";
	std::cin >> ExNumber;
	std::cout << std::endl;
	system("cls"); // clear screen. Avoid clrscr() method from <conio.h> as its non-std cpp lib
	std::cout << "*** EXERCISE NUMBER " << ExNumber << " ***" << std::endl << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush buffer


	switch (ExNumber) {
	case 1:
		std::cout << "Let's see if a sentence / word you entered is a palindrome." << std::endl << std::endl;;
		PalindromeCheck();
		break;

	case 2:
		std::cout << "Let's sort some numbers! Enter some numbers and watch them get sorted properly." << std::endl << std::endl;
		SortArray();
		break;

	case 3:
		std::cout << "Its a FizzBuzz game. Enter a number and the program will print 0 to your choosen number with a catch!" << std::endl << std::endl;
		FizzBuzz();
		break;

	case 4:
		std::cout << "Let's see if a sequence of numbers you entered is bitonic." << std::endl << std::endl;
		BitonicSequence();
		break;

	case 5:
		std::cout << "Enter a number and watch it print a sequence of factorals." << std::endl << std::endl;
		RecursiveFactoralSeq();
		break;

	case 6:
		std::cout << "Where in the chess board can your horse piece move?" << std::endl << std::endl;
		HorsePlay();
		break;

	case 7:
		std::cout << "Don't mind me while I create a class and do some operator overloading (program does not require user input, the code is more impt)" << std::endl << std::endl;
		ComplexNumbers();
		break;

	case 8:
		std::cout << "Hold up! Is your IP address valid?" << std::endl << std::endl;
		IPCheck();
		break;

	case 9:
		std::cout << "Move along...nothing to see here. Just me debugging some code without bug spray." << std::endl << std::endl;
		debugCode();
		break;

	case 10:
		std::cout << "LETS PLAY TIC TAC TOE! Grab a friend or play with the computer!" << std::endl << std::endl;
		Main_TicTacToe();
		break;

	case 11:
		std::cout << "Are the people in the csv file relatives? Let's find out!" << std::endl << std::endl;
		FindRelatives();
		break;

	case 12:
		std::cout << "How old are you...in days?" << std::endl << std::endl;
		AgeInDays();
		break;

	}

	std::cout << std::endl;
	std::cout << "*** PROGRAM ENDED ***" << std::endl;
	char endchar;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush buffer
	std::cout << "Press 'e' to exit" << std::endl;
	endchar = std::getchar();

	return 0;
}