#include <iostream> // used for input & output streams
#include <conio.h> // used for getch()
#include <limits> // used for garbage input
#include <ctime> // used for the random number generator
#include <chrono> // used to keep track of the time stamps
#include <fstream> // used for writing log files
#include <sstream> // used for the oss type to put the time stamp inside a string
#include <filesystem> // used for the folder directories
#include "sorter.h" // includes the sorter file and its function

#define SORT_ASCENDED true // used for file readability

const int LIMIT = 1000; // set a limit for the range of numbers that will never be changed on runtime

// using namespaces to shorten SPECIFIC use cases of std
using std::cout;
using std::ofstream;
using std::cin;
using std::chrono::system_clock;

// This class handles logging user actions when they use the program.
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
			std::filesystem::create_directory("Logs"); // If the "Logs" folder does not exist yet, we'll create one.
			cout << timeStamp;
			
			oss << local_tm.tm_year + 1900 << '-' << local_tm.tm_mon + 1 << '-' << local_tm.tm_mday; // +1900 and +1 is there to properly set the date to now.
			fileName = oss.str(); // combine the values together.
			fileName += ".txt";
			
			pathFile += fileName;
		};
		
		// Set the Timestamp to Whatever Time it is now
		void setTimeStamp()
		{
			tt = system_clock::to_time_t(system_clock::now());
			timeStamp = ctime(&tt);
		};
		
		// Get the Timestamp Value
		std::string getTimeStamp()
		{
			setTimeStamp();
			return timeStamp;
		};
		
		// Creates and Edits Existing Log Files
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
		
		// Only called when getNumberList is true from createNewLog()
		void displayNumberList(int numList[], int size)
		{
			// Iterate through each number and concatenate them inside the fullList string.
			std::string fullList;
			for(int i = 0; i < size; i++)
			{
				fullList += std::to_string(numList[i]);
				if(i != size - 1)
				{
					fullList += '-';
				}
			}
			
			fullList += "\n\n";
			createNewLog(fullList);
		};
};

// Declaring Functioons
void startUpMessage();
void fillList(int nums[], int size);


// Main Function
int main()
{
	srand(time(NULL)); // generate new random seed for the random number generator

	// Instantiate all necessary variables
	Logger Logs;
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
					arraySize < 10 || arraySize > 999 ? cout << "\nError, please input a valid number from 10-999: " : cout << "";
				}while(arraySize < 10 || arraySize > 999);
				
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