// Ex2: Sorting an int array
// Sort an integer array depending on user input
// Use a regular array and do not use any sorting functions from a library.

#include"CommonHeader.h"
enum FindType { Ascend = 0, Descend };

void SortArrayAlgo(int Arr[], int ArrSize, FindType FindType);
void PrintArrayElements(int Arr[], int ArrSize);


void SortArray() {
	// Step 0: Initialise all variables
	const int ArrLimit = 100;
	int Arr[ArrLimit] = { 0 };
	FindType SortingOrder;
	int SortingOrderTemp;
	int ArrSize;
	int idx;
	bool check1 = true;

	// Step 1: Asks user to enter length of array --> values of array --> type of sort (ascend or descend)
	while (check1) {
		std::cout << "Enter length of array (MAX LIMIT 100): ";
		std::cin >> ArrSize;

		if (ArrSize > 0 && ArrSize < ArrLimit) {
			check1 = false;
		}
		else {
			std::cout << "Entered invalid array size\n";
		}
	}
	check1 = true;

	std::cout << "Enter array values (INTEGER VALUES ONLY): \n";
	for (idx = 0; idx < ArrSize; idx++) {
		std::cin >> Arr[idx];
	}
	std::cout << std::endl;

	while (check1) {
		std::cout << "Sort type. 1 - Ascend Order. 2 - Descend Order: ";
		std::cin >> SortingOrderTemp;

		switch (SortingOrderTemp) {
		case 1:
			SortingOrder = Ascend;
			check1 = false;
			break;

		case 2:
			SortingOrder = Descend;
			check1 = false;
			break;

		default:
			std::cout << "Wrong value entered! \n";
			break;
		}
	}
	check1 = true;

	std::cout << "ORIGINAL ARRAY ORDER: ";
	PrintArrayElements(Arr, ArrSize);
	std::cout << std::endl;

	// Step 2: Sort array
	SortArrayAlgo(Arr, ArrSize, SortingOrder);

	// Step 3: Print out sorted array
	std::cout << "NEW ARRAY ORDER: ";
	PrintArrayElements(Arr, ArrSize);
	std::cout << std::endl;

}

// Function implements a modified version of the Selection Sort algo. It finds the min & max value and shifts them to the left & right most bounds respectively for each pass. After each pass, 
// the boundaries shift closer to the middle of the array.
void SortArrayAlgo(int Arr[], int ArrSize, FindType FindType) {
	// Modified selection sort algo
	int idx1, idx2, MinValue, MaxValue, MinValueIdx, MaxValueIdx, LeftMostEntry, RightMostEntry, LeftMostEntryIdx, RightMostEntryIdx, tempDescend;

	for (idx1 = 0; idx1 < (ArrSize / 2); idx1++) {
		// Initialise for new pass
		MinValue = Arr[idx1];
		MaxValue = Arr[idx1];
		MinValueIdx = idx1;
		MaxValueIdx = idx1;
		LeftMostEntryIdx = idx1;
		RightMostEntryIdx = ArrSize - (1 + idx1);

		// Finding Min and Max values for each pass
		for (idx2 = idx1; idx2 < (ArrSize - idx1); idx2++) {
			if (Arr[idx2] < MinValue) {
				MinValue = Arr[idx2];
				MinValueIdx = idx2;
			}
			if (Arr[idx2] > MaxValue) {
				MaxValue = Arr[idx2];
				MaxValueIdx = idx2;
			}
		}

		// Shifting Min Values to the left most end 
		LeftMostEntry = Arr[LeftMostEntryIdx];
		Arr[LeftMostEntryIdx] = MinValue;
		Arr[MinValueIdx] = LeftMostEntry;

		if (MaxValueIdx == LeftMostEntryIdx) { // Need to update MaxValueIdx if it shifts position due to it being on the left most entry idx
			MaxValueIdx = MinValueIdx;
		}

		// Shifting Max Values to the right most end
		RightMostEntry = Arr[RightMostEntryIdx];
		Arr[RightMostEntryIdx] = MaxValue;

		/* prevent situation if the max value index is the left most entry which has been shifted from above operations --> erase min value on the left most entry --> duplicate values!
		 also ensuring min value index is not right most entry else will result in right most entry being re-assigned as the min value --> duplicate values!
		(imagine swapping operation with min value at right most and max value at left most entry) */
		if (MaxValueIdx == LeftMostEntryIdx && MinValueIdx != RightMostEntryIdx) {
			Arr[MinValueIdx] = RightMostEntry;
		}
		else {
			Arr[MaxValueIdx] = RightMostEntry;
		}

	}

	if (FindType == Ascend) {
		return;
	}

	// Rearrange array in descending order
	for (idx1 = 0; idx1 < (ArrSize / 2); idx1++) {
		RightMostEntryIdx = ArrSize - (1 + idx1);

		tempDescend = Arr[idx1];
		Arr[idx1] = Arr[RightMostEntryIdx];
		Arr[RightMostEntryIdx] = tempDescend;
	}
}

void PrintArrayElements(int Arr[], int ArrSize) {
	int idx;

	for (idx = 0; idx < ArrSize;idx++) {
		std::cout << Arr[idx] << " ";
	}
}