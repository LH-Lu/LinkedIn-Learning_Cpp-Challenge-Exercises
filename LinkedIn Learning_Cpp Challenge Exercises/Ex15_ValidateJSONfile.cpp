// Ex15: Validate JSON file

// Write an application that validates a JSON file
// For a valid JSON file
//  Ensure balance of brackets [ ], braces { } and quotes " " are valid
//  For simplicity, count only double quotes " " + ignore everything between quotes
//  Use the JSON file given in the exercise

// Unacceptable sequences
//  }{{[]} {[]}} --> begins with closing brace + unbalanced --> fail
//  {{[}] {[]}} --> brackets overlapping brace --> fail

#include"CommonHeader.h"
#include"ExHeader.h"
#include<vector>
#include<fstream> // file handling

void ValidateJSON(){

	// Step 0: Initialise global variables
	std::vector<char> jsonBlocks;

	// Step 1: Open JSON file --> copy all brackets, braces and quotes in order (from top to bottom) into a vector, ignoring all contents within quotes --> close file
	std::ifstream JSONFile;
	const std::string FileName = "jason.JSON";

	std::string tempLine;
	int LineLength, idx;

	bool checkQuote = false;

	JSONFile.open(FileName);
	if (!JSONFile.is_open()) {
		std::cout << "File unable to open. Ending program. Check to ensure file " << FileName << " is located in same directory folder as all cpp exercise files." << std::endl;
		return;
	}

	while (std::getline(JSONFile, tempLine)) {
		
		if (JSONFile.bad() || JSONFile.fail()) {
			std::cout << "Reading error. Ending program." << std::endl;
			JSONFile.close();
			return;
		}

		LineLength = tempLine.length();
		for (idx = 0; idx < LineLength; idx++) {
			if (tempLine[idx] == '{' || tempLine[idx] == '}' || tempLine[idx] == '[' || tempLine[idx] == ']' || tempLine[idx] == '"') {
				if (tempLine[idx] == '"') {
					jsonBlocks.push_back(tempLine[idx]);
					checkQuote = !checkQuote;
				}
				
				if (checkQuote == false && tempLine[idx] != '"') {
					jsonBlocks.push_back(tempLine[idx]);
				}
			}
		}
	}

	JSONFile.close();

	// Step 2: Validate JSON file by checking balance of {}, [] and ""
	int VectorLength = jsonBlocks.size();
	int BalanceBraces = 0;
	int BalanceBrackets = 0;
	int BalanceQuotes = 0;
	int IdxBeforeStartQuote;

	bool checkOverlap = false;
	checkQuote = false;

	for (idx = 0; idx < VectorLength; idx++) {
		
		if (jsonBlocks[idx] == '{') {
			BalanceBraces++;
		}

		if (jsonBlocks[idx] == '}') {
			if (jsonBlocks[idx - 1] == '[') {
				checkOverlap = true;
				break;
			}
			if (jsonBlocks[idx - 1] == '"') {
				if (jsonBlocks[IdxBeforeStartQuote] == '[') {
					checkOverlap = true;
					break;
				}
			}
			BalanceBraces--;
		}

		if (jsonBlocks[idx] == '[') {
			BalanceBrackets++;
		}

		if (jsonBlocks[idx] == ']') {
			if (jsonBlocks[idx - 1] == '{') {
				checkOverlap = true;
				break;
			}
			if (jsonBlocks[idx - 1] == '"') {
				if (jsonBlocks[IdxBeforeStartQuote] == '{') {
					checkOverlap = true;
					break;
				}
			}
			BalanceBrackets--;
		}

		if (jsonBlocks[idx] == '"') {
			if (checkQuote == false) { 
				BalanceQuotes++; 
				IdxBeforeStartQuote = idx - 1;
			}
			else {
				BalanceQuotes--;
			}
			checkQuote = !checkQuote;
		}
	}

	// Step 3: Print result
	bool checkJSONvalid;

	if (checkOverlap == false && BalanceBraces == 0 && BalanceBrackets == 0 && BalanceQuotes == 0) {
		checkJSONvalid = true;
	}
	else {
		checkJSONvalid = false;
	}

	std::cout << "The JSON file is: " << (checkJSONvalid == true ? "VALID" : "INVALID") << std::endl;

}