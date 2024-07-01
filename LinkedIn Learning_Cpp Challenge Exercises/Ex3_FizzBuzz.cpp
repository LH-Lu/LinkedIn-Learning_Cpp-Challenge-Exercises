// Ex3: Fizz Buzz
// Fizz Buzz game
// Program prints sequence of int from 1 to n (n is user defined positive integer)
// But multiples of 3 replaced with "Fizz"
//  multiples of 5 replaced with "Buzz"
//  multiples of 3 and 5 replaced with "FizzBuzz"


#include"CommonHeader.h"
#include"ExHeader.h"

bool MultipleCheck(int idx, int multiple, bool PreviousFizzBuzzCheck, std::string PrintString);

void FizzBuzz() {

	// Step 0: Initialise variables
	int n, idx;
	bool check1 = true;
	bool FizzBuzzCheck = false;


	// Step 1: Prompt user to enter n
	while (check1) {
		std::cout << "Enter a positive integer: ";
		std::cin >> n;

		if (n > 0) {
			check1 = false;
		}
		else {
			std::cout << "Please enter a positive integer!" << std::endl;
		}
	}
	check1 = true;

	// Step 2: Print sequence, replace required multiples with the required string
	for (idx = 1; idx <= n; idx++) {

		// Check if idx is a required multiple. If yes, print required string
		FizzBuzzCheck = MultipleCheck(idx, 3, FizzBuzzCheck, "Fizz");
		FizzBuzzCheck = MultipleCheck(idx, 5, FizzBuzzCheck, "Buzz");

		// If FizzBuzzCheck is false after all checks --> print value
		if (FizzBuzzCheck == false) {
			std::cout << idx;
		}

		// Re-initialise for next pass
		std::cout << std::endl;
		FizzBuzzCheck = false;

	}

}

bool MultipleCheck(int idx, int multiple, bool PreviousFizzBuzzCheck, std::string PrintString) {
	if (idx % multiple == 0) {
		std::cout << PrintString;
		return true;
	}

	if (PreviousFizzBuzzCheck == true) {
		return true;
	}

	return false;
}