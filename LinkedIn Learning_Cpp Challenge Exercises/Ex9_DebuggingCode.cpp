// C++ Code Challenges, LinkedIn Learning

// *** NOTE THIS CODE WAS DOWNLOADED FROM THE GITHUB REPO PROVIDED FOR THE COURSE ***
// *** EDITS MADE TO ENSURE THIS CODE SEGMENT WORKS WITH PROGRAM STRUCTURE DENOTED WITH /// AS COMMENTS ***
// 
// *** EDITS MADE AS PART OF THIS COURSE WILL BE NOTED WITH '@' IN THE COMMENT LINE ***
// 
// Challenge #9: Fixing Faulty Code
// Fix the bugs in the provided code.
// The application is supposed to ask the user for a string, and print the number of vowels contained in the string.

// For example: 
// "I love my dog" has 4 vowels, "education" has 5 vowels, and "Sly spy by my crypt" has 0 vowels.

//#include <string> /// removed as already included in CommonHeader.h header file
#include"CommonHeader.h"
#include"ExHeader.h"

// vowel_count()
// Summary: This function counts the number of vowels in an incoming string.
// Arguments:
//           str: The string to analyze.
// Returns: An integer with the vowel count.
int vowel_count(std::string str){ // @ remove const string data type to just string data type to allow modification of string argument
    int count=0;
    int i; // @ variable i was declared in original code piece given but its tidier to declare everything at the beginning (also I dont really like the use of the letter i...calling it idx would be better for code reading)

    //for(int i; i<str.length(); i++) // @ variable i not initialised with start value for the for-loop
    for (i = 0; i < str.length(); i++) {
        str[i] = (char)std::tolower(str[i]); // @ code did not account for upper case char. Need to convert any upper case char to lower case char

        switch (str[i]) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            count++;
        }
    } // @ missing } in the for loop block
    return count;
}

// Faulty code, main()
// Summary: This application ask the user for a string, and prints the number of vowels in it.

//void main(){ /// removed and replaced as a void function in order to work with overall program structure
void debugCode() {
    std::string input; 
    std::cout << "Enter some text: " << std::flush;
    //std::cin >> input;
    std::getline(std::cin, input); // @ replaced cin with getline as a method to take in string as cin does not take in blankspaces --> will give wrong vowel count value
    std::cout << "\nThe text you entered contains " << vowel_count(input) << " vowels.\n\n";
}

 