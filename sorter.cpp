#include <iostream>
#include <conio.h>
#include "sorter.h"

void bubbleSort(int numberList[], bool sortAscended, int size)
{
	sortAscended == true ? std::cout << "--SORTING THROUGH ASCENDED--\n" : std::cout << "--SORTING THROUGH DESCENDED--\n";
	int temp;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size - i - 1; j++)
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

void viewNumbers(int numList[], int size)
{
	std::cout << "Viewing all numbers:\n";
	
	for(int i = 0; i < size; i++)
	{
		std::cout << numList[i] << ", " ;
	}
	
	std::cout << '\n';
	
	std::cout << "**********************************************\n";
}