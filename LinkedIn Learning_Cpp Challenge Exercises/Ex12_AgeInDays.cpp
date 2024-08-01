// Ex12: Find a user's age in days

// Take in a user's birthday and print their age in days
// Call bluff if the user claims to be over 120 years old

#include"CommonHeader.h"
#include"ExHeader.h"
#include<chrono>

// Takes in month in MMM format and returns in integer MM format
int MMMtoi(std::string MonthMMMFormat) {

	const std::string MMM[13] = { " ", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	int idx;
	for (idx = 1; idx < 13; idx++) {
		if (MonthMMMFormat.compare(MMM[idx]) == 0) {
			return idx;
		}
	}
	return 0;
}

// Check if a year is a leap year
bool IsLeapYear(int Year) {
	if (Year % 4 != 0) {
		return false;
	}
	if (Year % 100 != 0) {
		return true;
	}
	if (Year % 400 != 0) {
		return false;
	}
	return true;
}

void AgeInDays() {
	// Step 0: Initialise variables + get date now
	int UserBdayDay, UserBdayMonth, UserBdayYear;
	const int NumOfDaysRegularMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	std::time_t TimeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // get the current system time (in time_t data type)
	char TimeC_Str[26];
	ctime_s(TimeC_Str, sizeof TimeC_Str, &TimeNow); // ctime_s returns a char* (i.e a C-style string) of the current time
	std::string TimeCpp_Str(TimeC_Str); // convert from C-style string to C++ string

	int DayNow, MonthNow, YearNow;
	DayNow = std::stoi(TimeCpp_Str.substr(8, 2)); // Conver the days to integer
	MonthNow = MMMtoi(TimeCpp_Str.substr(4, 3)); // Convert the month to integer
	YearNow = std::stoi(TimeCpp_Str.substr(20, 4)); // Convert the year to integer

	//std::cout << "Now is: " << TimeCpp_Str; // debug
	//std::cout << "Today's date is (DD-MM-YYY): " << DayNow << "-" << MonthNow << "-" << YearNow << std::endl; // debug

	// Step 1: Get user birthday
	bool check1 = false;
	while (!check1) {
		std::cout << "Enter your birthday" << std::endl;;
		std::cout << "Day in DD format: ";
		std::cin >> UserBdayDay;

		std::cout << "Month in MM format: ";
		std::cin >> UserBdayMonth;

		std::cout << "Year in YYYY format: ";
		std::cin >> UserBdayYear;

		if (UserBdayYear > YearNow || (UserBdayYear == YearNow && UserBdayMonth > MonthNow) || (UserBdayYear == YearNow && UserBdayMonth == MonthNow && UserBdayDay > DayNow)) {
			std::cout << "Surely you can't be born in the future now can ye?" << std::endl << std::endl;
			continue;
		}

		if (UserBdayMonth < 1 || UserBdayMonth > 12) {
			std::cout << "Wrong month entered! There's only 12 months in a year!" << std::endl << std::endl;
			continue;
		}

		if (UserBdayDay < 1 || (UserBdayYear % 4 != 0 && UserBdayDay > NumOfDaysRegularMonth[UserBdayMonth]) || (UserBdayYear % 4 == 0 && UserBdayMonth == 2 && UserBdayDay > 29)) {
			std::cout << "There's no such day in the month you entered." << std::endl << std::endl;
			continue;
		}

		check1 = true;
	}
	std::cout << "\nYour birthday is: " << UserBdayDay << "-" << UserBdayMonth << "-" << UserBdayYear << std::endl;
	if (UserBdayDay == DayNow && UserBdayMonth == MonthNow && UserBdayYear == YearNow) {
		std::cout << "HAPPY BIRTHDAYYYYY" << std::endl;
	}

	// Step 2: Calculate age in years --> call bluff if more than 120 years old
	const int AgeYearBluff = 120;
	if (YearNow - UserBdayYear >= AgeYearBluff) {
		std::cout << "Bluff! You can't be more than 120 years old!" << std::endl;
		return;
	}

	// Step 3: Calcualte age in days (note leap years) --> 
	// In current year, minus number of days to next bday if bday hasnt elapsed / add number of days from last birthday if bday has elapsed --> 
	// count the total number of days in the year between this year and the year the user was born
	int countDays = 0;

	if (UserBdayDay > DayNow) {
		countDays = DayNow - UserBdayDay;
	}
	else if (UserBdayDay < DayNow) {
		countDays = DayNow - UserBdayDay;
	}
	else if (UserBdayDay == DayNow) {
		// do nothing
	}

	int IdxMonth;
	if (UserBdayMonth > MonthNow) {
		for (IdxMonth = MonthNow; IdxMonth < UserBdayMonth; IdxMonth++) {
			countDays = countDays - NumOfDaysRegularMonth[IdxMonth];
			if (IdxMonth == 2 && IsLeapYear(YearNow) == true) {
				countDays--;
			}
		}
	}
	else if (UserBdayMonth < MonthNow) {
		for (IdxMonth = MonthNow; IdxMonth > UserBdayMonth; IdxMonth--) {
			countDays = countDays + NumOfDaysRegularMonth[IdxMonth];
			if (IdxMonth == 2 && IsLeapYear(YearNow) == true) {
				countDays = countDays++;
			}
		}
	}
	else if (UserBdayMonth == MonthNow) {
		// do nothing
	}
	
	int IdxYear;
	bool checkLeapYear;
	for (IdxYear = YearNow; IdxYear > UserBdayYear; IdxYear--) {
		checkLeapYear = IsLeapYear(IdxYear);
		if (checkLeapYear == true) {
			countDays = countDays + 366;
		}
		if (checkLeapYear == false) {
			countDays = countDays + 365;
		}
	}

	// Step 4: Print result
	std::cout << "Number of days since you were born: " << countDays << std::endl;
}

