// Ex5: Recursive Factoral Sequence
// Write a recursive function to print sequence of factorials from 0! to n! 
// where n is a user generated integer between 1 to 10 (inclusive)
// Note,
//  Function to calculate the factorial must be recursive
//  Calculate each element only once (i.e dont call the recursive function n times for n!)
// 
// Example output from program: n = 4 --> print: {1, 1, 2, 6, 24} i.e {0!, 1!, 2!, 3!, 4!}



#include"CommonHeader.h"
#include"ExHeader.h"


int Factorial(int n);

void RecursiveFactoralSeq() {

	// Step 0: Initialise variables
	int n;
	bool check1 = true;


	// Step 1: Ask user for n
	while (check1) {
		std::cout << "Factorial sequence generator from 0! to n!. Enter value of n (between 1 and 10 only): ";
		std::cin >> n;

		if (n > 0 && n < 11) {
			check1 = false;
			break;
		}
		std::cout << "Wrong value entered!" << std::endl;
	}
	std::cout << std::endl;

	// Step 2 - 3: Step into recursive function to calculate factoral seqeunce + print factoral sequence
	std::cout << "Factorial sequence: ";
	Factorial(n);
	std::cout << std::endl;

}

int Factorial(int n) {
	
	int ReturnValue;

	if (n == 0) {
		ReturnValue = 1; // Base case
	}
	else {
		ReturnValue = n * Factorial(n - 1);
	}

	std::cout << ReturnValue << " ";
	return ReturnValue;
}