#include <iostream>
#include <conio.h>
#include <limits>
#include <ctime>
#include "sorter.h"

#define SORT_ASCENDED true

// TO IMPROVE:
// 1) Allow users to input how much numbers they'd like to randomly generate
// 2) Allow users to input the range for each number
// 3) Add templates to support decimal numbers
// 4) Add a logging system

using std::cout;
using std::cin;

void startUpMessage();
void fillList(int nums[50]);

int main()
{
	srand(time(NULL));
	
	int numberList[50] = {};
	fillList(numberList);
	
	bool running = true;
	int menuInput = 0;
	
	cout << "-----BOOTING UP NUMBER SORTER APPLICATION-----\n";
	cout << "**********************************************\n";
	
	do{
		startUpMessage();
		cin >> menuInput;
		
		std::cin.clear(); // clear any error flags at cin.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip to new line and proceed with the program for no further issues.
		
		switch(menuInput)
		{
			case 1: // User will view numbers
				viewNumbers(numberList);
				break;
			case 2: // User will randomly generate the list with numbers
				fillList(numberList);
				viewNumbers(numberList);
				break;
			case 3: // User will sort numbers in ascended
				bubbleSort(numberList, SORT_ASCENDED);
				viewNumbers(numberList);
				break;
			case 4: // User will sort numbers in descended
				bubbleSort(numberList, !SORT_ASCENDED);
				viewNumbers(numberList);
				break;
			case 5: // User will exit the program
				running = false;
				break;
			default: // User has input something invalid, let's remind them!
				cout << "=-=-=-=-=-=-=-=-=-=-=-=\n";
				cout << "Invalid input! Please type one of the following corresponding values\n";
				cout << "=-=-=-=-=-=-=-=-=-=-=-=\n";
		}
	}while(running);
	
	cout << "**********************************************\n";
	cout << "-----ENDING NUMBER SORTER APPLICATION-----\n";
	
	getch();
	return 0;
}

void startUpMessage()
{
	cout << "Type '1' to View the Current Set of Numbers\n";
	cout << "Type '2' to Generate New Values\n";
	cout << "Type '3' to Sort Numbers Through Ascended\n";
	cout << "Type '4' to Sort Numbers Through Descended\n";
	cout << "Type '5' to Exit Program\n";
	cout << "Please type the number here: ";
}

void fillList(int nums[50])
{
	cout << "Generating numbers...\n";
	for(int i = 0; i < 50; i++)
	{
		nums[i] = (rand() % 1000) + 1;
	}
}