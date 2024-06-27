// This is the main function --> access to individual exercises

#include"CommonHeader.h"
#include"ExHeader.h"


int main() {

	int ExNumber = -1;

	std::cout << "Please enter Exercise Number: ";
	std::cin >> ExNumber;
	std::cout << std::endl;
	std::cout << "*** EXERCISE NUMBER " << ExNumber << " ***" << std::endl << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush buffer


	switch (ExNumber) {
	case 1:
		PalindromeCheck();
		break;
	}

	std::cout << std::endl;
	std::cout << "*** PROGRAM ENDING ***" << std::endl;

	return 0;
}