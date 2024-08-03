// Ex14: Reflex Game

// Write an application that:
//  Waits for a random delay between 4 and 10 seconds
//  Ask user to type a random three letter word that comes from a list of 10 three-lettered words
//  Print success message if user types the word correctly within 2 seconds. Else print a failure message
//  Ignore case sensitivity for user input

// Note, this exercise showcases 1) creating pseudo random numbers in C++ 2) Display current system time 3) Pause for a define time 4) Measure time taken to do an operation

#include"CommonHeader.h"
#include"ExHeader.h"
#include<chrono> // time functions
#include<thread> // for pause function
#include<cstdlib> // rand() function
#include<algorithm> // for using transform
//#include<cctype> // for using toupper


// Function returns a pseudo random number based on upper and lower bounds argument
int RandNum(const int UpperBound, const int LowerBound) {
	srand(std::time(0)); // seed rand() to make the random numbers generated more random. must be placed before first instance of rand()
	return (rand() % (UpperBound - LowerBound + 1) + LowerBound);
}

void ReflexGame() {

	// Step 0: Initialise global variables
	const int MaxListSize = 10;
	const double InputTimeLimitSeconds = 2.0;
	const int MaxWordLength = 3;

	std::string ListOfWords[MaxListSize] = { "CAT", "DOG", "BUN", "PIG", "COW", "CAN", "BEN", "BUS", "CAR", "TAN" };
	std::string UserWord;

	int RandListIdx = RandNum(9, 0);
	int RandomDelay = RandNum(10, 4);

	int idx;
	bool check1 = false;

	// Step 0A: Prints current time (to practice and consolidate all possible time functions and algo into one exercise)
	std::time_t TimeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // get the current system time (in time_t data type)
	char TimeC_Str[26];
	ctime_s(TimeC_Str, sizeof TimeC_Str, &TimeNow); // ctime returns a char* (i.e a C-style string)
	std::string TimeCpp_Str(TimeC_Str); // convert from C-style string to C++ string

	std::cout << "DATE AND TIME NOW: " << TimeCpp_Str << std::endl;

	// Step 1: Asks user whether he is ready to begin
	char UserConfirm;
	while (!check1) {
		std::cout << "Are you ready (y/n)? - ";
		UserConfirm = std::getchar();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush buffer

		if (UserConfirm == 'y') {
			break;
		}

		if (UserConfirm == 'n') {
			std::cout << "Its okay, take your time!" << std::endl;
		}
		else {
			std::cout << "I didn't quite catch that. Please re-enter your response ><" << std::endl;
		}
	}
	std::cout << std::endl;

	// Step 2: Wait for random delay of 4 - 10 seconds
	for (idx = 1; idx <= RandomDelay; idx++) {
		std::this_thread::sleep_for(std::chrono::seconds(1)); // pause for 1 seconds
		std::cout << "*" << std::endl;
	}
	std::cout << std::endl;

	// Step 3: Request user to write 3-letter word randomly chosen from a list of 10 3-letter words + measure time taken to input
	std::cout << "Please enter the word: " << ListOfWords[RandListIdx] << std::endl;
	std::cout << "> ";

	auto StartTime = std::chrono::high_resolution_clock::now(); // get starting time point
	std::getline(std::cin, UserWord);
	auto EndTime = std::chrono::high_resolution_clock::now(); // get ending time point
	auto Duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count(); // get duration of operation (casted into ms)

	// Step 4: Validate time taken + Validate whether word entered match
	bool CheckWord = false;
	bool CheckTimeTaken = false;
	bool CheckOverall = false;

	// check word legnth
	if (UserWord.length() > MaxWordLength) {
		CheckWord = false;
	}
	else { 
		CheckWord = true; 
	}

	// check if input correct
	if (CheckWord == true) {
		std::transform(UserWord.begin(), UserWord.end(), UserWord.begin(), std::toupper); // convert string to all uppercase

		if (UserWord.find(ListOfWords[RandListIdx]) == std::string::npos) { // User entered word does not match 
			CheckWord = false;
		}
		else {
			CheckWord = true;
		}
	}

	// check if meet time limit
	if ((Duration/1000.0) <= InputTimeLimitSeconds) {
		CheckTimeTaken = true;
	}

	// check if overall task successful
	if (CheckWord == true && CheckTimeTaken == true) {
		CheckOverall = true;
	}

	std::cout << "Word match: " << (CheckWord == true ? "PASS" : "FAIL") << std::endl;
	std::cout << "Time limit met: " << (CheckTimeTaken == true ? "PASS" : "FAIL") << std::endl;
	std::cout << "Time taken: " << Duration / 1000.0 << " seconds" << std::endl << std::endl;
	std::cout << "Overall: " << (CheckOverall == true ? "PASS" : "FAIL") << std::endl;

}