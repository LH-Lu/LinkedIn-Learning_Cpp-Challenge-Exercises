// Ex11: Find Relatives

// Read a csv file and display a message if the first pair of people are related
// CSV format: Entries separated by commas, names separated by spaces
// Assume all entries only have one first and last name

#include"CommonHeader.h"
#include"ExHeader.h"
#include<vector>
#include<fstream>

void FindRelatives() {

	// Step 0: Initialise Variables
	std::string FileName;
	std::ifstream File;
	std::vector<std::string> Names;

	// Step 1: Open File --> Read Contents to Memory --> Close File
	std::string TempStr;

	std::cout << "Enter file name: ";
	std::getline(std::cin, FileName);

	File.open(FileName);
	if (!File.is_open()) {
		std::cout << "File did not open successfully! Please ensure file name entered is correct and file is located within the same folder as the .cpp files!" << std::endl;
		return;
	}

	while (getline(File, TempStr, ',')) {
		if (File.bad() || File.fail()) {
			std::cout << "Reading error!" << std::endl;
			File.close();
			return;
		}
		
		Names.push_back(TempStr);
	}

	File.close();

	// Step 2: Compare names (using basic linear search algorithm) --> stop once found first pair of relatives and output the result
	int VectorLength, VectorIdx, CompareIdx;
	bool check1 = false;
	std::size_t SpacePos;
	std::string key1, key2;

	VectorLength = Names.size();

	for (VectorIdx = 0; VectorIdx < VectorLength; VectorIdx++) {
		SpacePos = Names[VectorIdx].find(" ");
		key1 = Names[VectorIdx].substr(0, SpacePos);
		key2 = Names[VectorIdx].substr(SpacePos + 1);

		for (CompareIdx = VectorIdx + 1; CompareIdx < VectorLength; CompareIdx++) {
			// Using the find function rather than the compare function as able to check the presence of key1 / key2 sub strings in the entire string without breaking the string up into its consituent words
			if (Names[CompareIdx].find(key1) != std::string::npos) { // If the words stored in key1 / key2 not found in the string --> find function will return std::string::npos
				check1 = true;
				break;
			}
			if (Names[CompareIdx].find(key2) != std::string::npos) {
				check1 = true;
				break;
			}
		}

		if (check1 == true) {
			std::cout << Names[VectorIdx] << " and " << Names[CompareIdx] << " are possible relatives." << std::endl;
			return;
		}
	}

	std::cout << "None of the names indicate possible relatives." << std::endl;
}