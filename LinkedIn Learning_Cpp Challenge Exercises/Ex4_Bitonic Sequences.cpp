// Ex4: Bitonic Sequence
// Bitonic Sequences are sequences where there must be no more than one ascending and one descending order in the entire sequence when looped.
// For example,
// 1 2 3 4 3  is a bitonic sequence as it rises between the first and fourth element before descending to the last and back to the first element 
// (i.e ascend 1 -> 2 -> 3 -> 4    then descend 4 -> 3 -------> 1)
// 
// 3 2 3 4 1 is not bitonic b'cos there is two sets of ascending and two sets of descending order
// (i.e descend 3 -> 2    then ascend 2 -> 3 -> 4    descend 4 -> 1    then ascend 1 -------> 3)
//
// Note, regions of consantness between elements are not counted so 1 2 2 3 4 is also a bitonic sequence and 2 2 2 2 2 are also bitonic sequence (technically they're called monotonic sequence)
//
// The program needs to take in a user defined STL vector and check whether it is bitonic


#include"CommonHeader.h"
#include"ExHeader.h"
#include<vector>
#include<algorithm>

void ContinuousOrderCheck(int StartIdx, int EndIdx, std::vector<int>& vec, int VectorSize, int& AscendCount, int& DescendCount);

void BitonicSequence() {

	// Step 0: Initialise variables
	std::vector<int> vec;
	int idx, UserValue, VectorSize;
	
	int AscendCount = 0;
	int DescendCount = 0;

	int MaxValueIdx, MinValueIdx;

	bool BitonicCheck = false;
	bool check1 = true;

	// Step 1: Enter sequence and reprint it
	while (check1) {
		std::cout << "Enter number of elements in sequence (min. 3): ";
		std::cin >> VectorSize;
		if (VectorSize > 2) {
			check1 = false;
		}
	}
	check1 = true;

	for (idx = 0; idx < VectorSize; idx++) {
		std::cout << "Enter integer value of NO. " << idx + 1 << " element: ";
		std::cin >> UserValue;

		vec.push_back(UserValue);
	}
	std::cout << std::endl;

	std::cout << "Sequence entered is: ";
	for (idx = 0; idx < VectorSize; idx++) {
		std::cout << vec[idx] << " ";
	}
	std::cout << std::endl;

	// Step 2: Check if sequence is bitonic (w/in sequence first)
	// Step 2.1: Find the max and min values' index. If all constant, MaxValueIdx == MinValueIdx
	MaxValueIdx = std::distance(vec.begin(), std::max_element(vec.begin(), vec.end()));
	MinValueIdx = std::distance(vec.begin(), std::min_element(vec.begin(), vec.end()));

	// Step 2.2: Check if there's a continuous descend from the max to the min and a continous ascend from the min to the max (regions of constant ignored)
	if (MaxValueIdx != MinValueIdx) {
		ContinuousOrderCheck(MaxValueIdx, MinValueIdx, vec, VectorSize, AscendCount, DescendCount);
		ContinuousOrderCheck(MinValueIdx, MaxValueIdx, vec, VectorSize, AscendCount, DescendCount);
	}

	// Step 2.3: Check if conditions of bitonic sequence met
	if (AscendCount == 1 && DescendCount == 1) {
		BitonicCheck = true;
	}
	if (MaxValueIdx == MinValueIdx) { // all elements constant situation
		BitonicCheck = true;
	}


	// Step 3: Output result
	std::cout << "The sequence entered is: ";
	switch(BitonicCheck) {
		case true:
			std::cout << "BITONIC";
			break;

		case false:
			std::cout << "NOT BITONIC";
			break;
	}

	std::cout << std::endl;

}

void ContinuousOrderCheck(int StartIdx, int EndIdx, std::vector<int>& vec, int VectorSize, int& AscendCount, int& DescendCount) {
	int idx = StartIdx;
	int CompareIdx = idx + 1;

	bool ExistingAscendOrder = false;
	bool ExistingDescendOrder = false;
	bool check1 = true;
	int FailSafeCount = 0;

	while (check1) {
		if (CompareIdx == VectorSize) {
			CompareIdx = 0;
		}

		if (vec[CompareIdx] > vec[idx]) {
			if (ExistingAscendOrder == false) {
				AscendCount++;
			}

			ExistingAscendOrder = true;
			ExistingDescendOrder = false;
		}

		if (vec[CompareIdx] < vec[idx]) {
			if (ExistingDescendOrder == false) {
				DescendCount++;
			}
			ExistingDescendOrder = true;
			ExistingAscendOrder = false;
		}

		// Exit clause
		if (CompareIdx == EndIdx) {
			check1 = false;
			break;
		}
		if (FailSafeCount > VectorSize * 2) {
			check1 = false;
			std::cout << "ERROR! INFINITE LOOP! \n";
			break;
		}

		// Prepare for next pass
		if (CompareIdx == 0) { // The pass was comparing last element with first element of vector --> next pass is comparing first and second element
			idx = 0;
		}
		else {
			idx++;
		}
		CompareIdx++;
	}
}