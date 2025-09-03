#include <iostream>
#include <conio.h>
#include "sorter.h"

// Bubble Sort Algorithm
void bubbleSort(int numberList[], bool sortAscended, int size)
{
	sortAscended == true ? std::cout << "--SORTING THROUGH ASCENDED--\n" : std::cout << "--SORTING THROUGH DESCENDED--\n"; // if sortAscended == true, then we'll output we're ascending it; vice versa.
	int temp; // create a temporary variable
	
	// Track if every number has been checked
	for(int i = 0; i < size; i++)
	{
		// Compare adjacent elements; since the elements are pushed to the BACK, we do not need to check there anymore.
		for(int j = 0; j < size - i - 1; j++)
		{
			if(sortAscended == true && numberList[j] > numberList[j + 1])
			{
				// The number next to us is LOWER than the current index : we'll switch the numbers. We'll also sort through ascended:
				temp = numberList[j]; // set temporary value to current index value
				
				// Switch the two values
				numberList[j] = numberList[j + 1];
				numberList[j + 1] = temp;
			}
			else if(sortAscended == false && numberList[j] < numberList[j + 1])
			{
				// // The number next to us is HIGHER than the current index : we'll switch the numbers. We'll also sort through descended:
				temp = numberList[j]; // set temporary value to current index value
				
				// Switch the two values
				numberList[j] = numberList[j + 1];
				numberList[j + 1] = temp;
			}
		}
	}
	
	std::cout << "Done sorting! Type any key to proceed...\n";
	getch();
}

// View Numbers
void viewNumbers(int numList[], int size)
{
	std::cout << "Viewing all numbers:\n";
	
	// Iterate through each integer inside numList, then output it.
	for(int i = 0; i < size; i++)
	{
		if(i == size - 1)
		{
			std::cout << numList[i];			
		}
		else
		{
			std::cout << numList[i] << ", " ;
		}
	}
	
	std::cout << '\n';
	
	std::cout << "**********************************************\n";
}