// Ex16: The Birthday Problem

// Create an application that simulates The Birthday Problem 1,000,000 times with n number of people in the group
// Where n is a user defined integer number
// i.e For 1,000,000 iterations, within a group of n people with random birthdays, pick a person and randomly assign him a bday. 
// Count number of people whose randomly assigned bday matches with the person you picked
// 
// Application shld display the probability of a bday match over the 1,000,000 iterations i.e (number of bday matches / number of iterations)
// 
// Use the application to prove that the probability of having at least 2 ppl with the same bday approx 0.5 in a group of 23 people (the bday paradox)
// Note, there are 366 different possible birthdays

#include"CommonHeader.h"
#include"ExHeader.h"
#include<vector>
#include<algorithm> // to use std::sort
#include<cstdlib> // for rand() function

// Within a group of n people with randomly assigned birthdays, find how many of them have matching birthdays
void FindNumMatchingBday(int& matches, const int& NumOfPeople, const int& LowerBound, const int& UpperBound) {
	int PeopleIdx;
	int* key = nullptr;

	std::vector<int> PeopleBday;
	
	// Randomly assign each person a bday. 
	// Birth dates are taken as unique numbers ranging from 1 - 366. Therefore 1 Jan = 1, 1 Feb = 32 and so on (note, #366 -> 29 Feb for leap years for simplicity sake)
	srand(std::time(0));
	for (PeopleIdx = 0; PeopleIdx < NumOfPeople; PeopleIdx++) {
		PeopleBday.push_back(rand() % (UpperBound - LowerBound + 1) + LowerBound);
	}

	// Sort vectors in ascending order
	std::sort(PeopleBday.begin(), PeopleBday.end());

	// Count number of matches
	key = &PeopleBday[0];
	for (PeopleIdx = 1; PeopleIdx < NumOfPeople; PeopleIdx++) {
		if (PeopleBday[PeopleIdx] == *key) {
			matches++;
		}
		else {
			key = &PeopleBday[PeopleIdx];
		}
	}
}

void BirthdayProblem() {

	// Step 0: Global variables
	const int TotalIterations = 100000; // 1 million iterations took too long
	const int NumOfUniqueBdayDates = 366;
	int NumOfPeople;
	int matches = 0;

	// Step 1: Get user input on number of people in the group
	bool check1 = false;
	while (!check1) {
		std::cout << "How many people do you want in your group? ";
		std::cin >> NumOfPeople;

		if (NumOfPeople < 2) {
			std::cout << "Needs to have more people in the group to have a possbility of matching birthdays (i.e you need 2 or more people in the group)" << std::endl;
		}
		else {
			break;
		}
	}

	// Step 2: Simulate the birthday problem
	int itr, PeopleIdx, key;
	const int LowerBound = 1;
	const int UpperBound = 366;

	if (NumOfPeople <= NumOfUniqueBdayDates) {
		for (itr = 0; itr < TotalIterations; itr++) {
			FindNumMatchingBday(matches, NumOfPeople, LowerBound, UpperBound);
			std::cout << "Completed iteration: " << itr + 1 << " / " << TotalIterations << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "Number of matches: " << matches << std::endl;
	std::cout << "Total number of iterations completed: " << TotalIterations << std::endl;

	// Step 3: Display probability of birthday matches over the 1,000,000 iterations
	std::cout << "The probability of a birthday match is: ";
	if (NumOfPeople > NumOfUniqueBdayDates) {
		std::cout << "1";
	}
	else {
		std::cout << (double)matches / TotalIterations;
	}
	std::cout << std::endl;
}
