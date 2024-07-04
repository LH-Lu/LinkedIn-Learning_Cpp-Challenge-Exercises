// Ex8: IP Address Checker
// Create a program that checks whether an IP address is valid
// Assume IPv4 address format
// Therefore, for an IP address to be valid:
//		Needs to have four numbers
//		Each number must be between 0 and 255 (inclusive)
// Examples of valid IP address: 158.25.2.33 and 192.168.0.1
// Examples of invalid IP addresses: 100.325.4 and 12.B5-33 FF


#include"ExHeader.h"
#include"CommonHeader.h"

bool is_IPValid(std::string IPAddress);

void IPCheck() {
	// Step 0: Initialise Variables
	std::string IPAddress;
	bool IPValid;

	// Step 1: Take in IP address input
	std::cout << "Enter IP address (IPv4 format): ";
	std::getline(std::cin, IPAddress);
	
	// Step 2: Check if IP address is valid
	IPValid = is_IPValid(IPAddress);

	// Step 3: Prints result
	std::cout << "IP address entered is: ";
	switch (IPValid){
	case true:
		std::cout << "VALID";
		break;

	case false:
		std::cout << "INVALID";
		break;
	}
	std::cout << std::endl;
}

bool is_IPValid(std::string IPAddress) {

	// Get length of string
	int idx;
	int StrLen = IPAddress.length();

	// Check 1 - Only Numbers and Periods present --> Correct no. of numbers (therefore, need to have only 3 "." detected, no more, no less) 
	const int NumOfPeriods = 3;
	int CountPeriods = 0;

	for (idx = 0; idx < StrLen; idx++) {

		// Check only digits and periods present
		if (!isdigit(IPAddress[idx])) {
			if (IPAddress[idx] != '.') {
				return false;
			}
		}
		
		if (IPAddress[idx] == '.' && idx != StrLen - 1) {
			CountPeriods++;
		}
	}
	if (CountPeriods != NumOfPeriods) {
		return false;
	}

	// Check 2 - Numbers are between 0 and 255 (inclusive)
	int DigitStartIdx = 0;
	int IPValue;
	const int IPValueMin = 0;
	const int IPValueMax = 255;

	for (idx = 0; idx < StrLen; idx++) {
		if (IPAddress[idx] == '.') {
			IPValue = std::stoi(IPAddress.substr(DigitStartIdx, idx - DigitStartIdx));
			if (IPValue < IPValueMin || IPValue > IPValueMax) {
				return false;
			}
			DigitStartIdx = idx + 1;
		}
	}

	return true;
}