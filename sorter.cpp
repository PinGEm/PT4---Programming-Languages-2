#include <iostream>
#include <conio.h>
#include "sorter.h"

void bubbleSort(int numberList[], bool sortAscended)
{
	sortAscended == true ? std::cout << "--SORTING THROUGH ASCENDED--\n" : std::cout << "--SORTING THROUGH DESCENDED--\n";
	int temp;
	for(int i = 0; i < 50; i++) // 50 TEMPORARY VALUE FOR NOW. WHEN I ALLOW USERS TO INPUT HOW MANY NUMBERS THEY WANT TO ADD THIS WILL CHANGE
	{
		for(int j = 0; j < 50 - i - 1; j++)
		{
			if(sortAscended == true && numberList[j] > numberList[j + 1])
			{
				temp = numberList[j];
				numberList[j] = numberList[j + 1];
				numberList[j + 1] = temp;
			}
			else if(sortAscended == false && numberList[j] < numberList[j + 1])
			{
				temp = numberList[j];
				numberList[j] = numberList[j + 1];
				numberList[j + 1] = temp;
			}
		}
	}
	
	std::cout << "Done sorting! Type any key to proceed...\n";
	getch();
}

void viewNumbers(int numList[])
{
	std::cout << "Viewing all 50 numbers:\n";
	int count = -1;
	
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			count++;
			std::cout << numList[count] << ',';
		}
		
		std::cout << '\n';
	}
	
	std::cout << "**********************************************\n";
}