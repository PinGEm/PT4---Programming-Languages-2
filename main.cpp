#include <iostream>
#include <conio.h>
#include <limits>
#include <ctime>
#include <chrono>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "sorter.h"

#define SORT_ASCENDED true

const int LIMIT = 1000;

using std::cout;
using std::ofstream;
using std::cin;
using std::chrono::system_clock;

class Logger
{
	private:
		// Time Stamp
		std::time_t tt = system_clock::to_time_t(system_clock::now());
		std::string timeStamp = ctime(&tt);
		
		// File Name
		tm local_tm = *localtime(&tt);
		std::ostringstream oss;
		std::string fileName;
		std::string pathFile = "Logs/";
	public:
		
		// When Class is Instantiated, do the following:
		Logger()
		{
			cout << timeStamp;
			
			oss << local_tm.tm_year + 1900 << '-' << local_tm.tm_mon + 1 << '-' << local_tm.tm_mday; // +1900 and +1 is there to properly set the date to now.
			fileName = oss.str(); // combine the values together.
			fileName += ".txt";
			
			pathFile += fileName;
		};
		
		void setTimeStamp()
		{
			tt = system_clock::to_time_t(system_clock::now());
			timeStamp = ctime(&tt);
		};
		
		std::string getTimeStamp()
		{
			setTimeStamp();
			return timeStamp;
		};
		
		void createNewLog(std::string message, bool getNumberList = false, int numList[] = {}, int size = 0)
		{
			// Create the file, or append it if it exists
			ofstream MyFile(pathFile, std::ios::app);
			
			// If for some reason the file doesn't open, immediately exit.
			if(!MyFile.is_open())
			{
				return;
			}
			
			// If we're getting a number list, call another function to handle it
			if(getNumberList)
			{
				displayNumberList(numList, size);
				return;
			}
			
			// Input the message in the file.
			MyFile << message;
			
			// Close the file to save memory
			MyFile.close();
		};
		
		void displayNumberList(int numList[] = {}, int size = 0)
		{
			for(int i = 0; i < size; i++)
			{
				if(i == size - 1)
				{
					createNewLog(std::__cxx11::to_string(numList[i]) + "\n\n", false, numList, size);
				}
				else if (i < size)
				{
					createNewLog(std::__cxx11::to_string(numList[i]) + "-", false, numList, size);
				}
			}
		};
};

void startUpMessage();
void fillList(int nums[], int size);

int main()
{
	Logger Logs;
	srand(time(NULL));
	
	int arraySize = 50;
	int* numberList = new int[arraySize];
	
	fillList(numberList, arraySize);
	
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
				viewNumbers(numberList, arraySize);
				break;
			case 2: // User will randomly generate the list with numbers
				delete[] numberList;
				
				cout << "How much numbers would you like to generate? (10-999): ";
				
				// Make the user give a valid input from 10 -> Whatever the LIMIT is
				do{
					cin >> arraySize;
					std::cin.clear(); // clear any error flags at cin.
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip to new line and proceed with the program for no further issues.
					arraySize < 10 || arraySize > LIMIT ? cout << "\nError, please input a valid number from 10-999: " : cout << "";
				}while(arraySize < 10 || arraySize > LIMIT);
				
				// Free memory, then fill the list again.
				numberList = new int[arraySize];
				fillList(numberList, arraySize);
				
				// Create Logs Files
				Logs.createNewLog(Logs.getTimeStamp().append("Generated a new set of numbers: \n"));
				Logs.createNewLog("", true, numberList, arraySize);
				
				// View Numbers Once Process is Completed
				viewNumbers(numberList, arraySize);
				break;
			case 3: // User will sort numbers in ascended
				bubbleSort(numberList, SORT_ASCENDED, arraySize);
				
				// Create Logs Files
				Logs.createNewLog(Logs.getTimeStamp().append("Reorganized numbers in ascending order: \n"));
				Logs.createNewLog("", true, numberList, arraySize);
				
				// View Numbers Once Process is Completed
				viewNumbers(numberList, arraySize);
				break;
			case 4: // User will sort numbers in descended
				bubbleSort(numberList, !SORT_ASCENDED, arraySize);
				
				// Create Logs Files
				Logs.createNewLog(Logs.getTimeStamp().append("Reorganized numbers in descending order: \n"));
				Logs.createNewLog("", true, numberList, arraySize);
				
				// View Numbers Once Process is Completed
				viewNumbers(numberList, arraySize);
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
	
	// Free memory
	delete[] numberList;
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

void fillList(int nums[], int size)
{
	// Generate New Numbers
	
	cout << "Generating numbers...\n";
	for(int i = 0; i < size; ++i)
	{
		nums[i] = (rand() % LIMIT) + 1;
	}
}