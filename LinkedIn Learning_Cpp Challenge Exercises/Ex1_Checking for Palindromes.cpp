// Ex1: Check for Palindromes
// Require user to enter a string
// Check if the string entered reads the same backwards as forwards. Ignore case of the characters. Must include all characters in the string
// If yes --> Palindromes (e.g level, step onno pets)
// If no --> not Palindromes (e.g don't nod)

#include"CommonHeader.h"

void PalindromeCheck() {
	
	// Step 0: Initialise all variables
	std::string UserString;
	bool CheckPalindrome = true;
	char tempBegin, tempEnd;
	int StrLength = -1;
	int idx;


	// Step 1: Request user for string input
	std::cout << "Please enter a string: ";
	std::getline(std::cin, UserString);

	// Step 2: Get string length
	StrLength = UserString.length();

	// Step 3: Check string entered reads the same backwards as forwards
	for (idx = 0; idx < (StrLength/2); idx++) {

		// Ensure chars for comparison is the same case. Note need to type cast std::toupper as it returns an int value
		tempBegin = (char)std::toupper(UserString[idx]);
		tempEnd = (char)std::toupper(UserString[StrLength - idx - 1]);

		// Ensure chars for comparison matches
		if (tempBegin != tempEnd) {
			CheckPalindrome = false;
			break;
		}
	}

	// Step 4: Output check result to user
	std::cout << "String entered is palindrome: ";
	switch (CheckPalindrome) {
	case true:
		std::cout << "YES";
		break;

	case false:
		std::cout << "NO";
		break;
	}
	std::cout << std::endl;
}