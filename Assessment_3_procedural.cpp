#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>


void displayRules(std::vector < std::vector <char>>& vect, int& ladies, int& men, int& children, int& ladiesToRemove, int& menToRemove, int& childrenToRemove, char& stops);

void menuSystem(std::vector < std::vector <char>>& vect, int& ladies, int& men, int& children, int& ladiesToRemove, int& menToRemove, int& childrenToRemove, char& stops);

void displayDefaultPlan(std::vector < std::vector <char>>& vect, int& ladies, int& men, int& children, char& stops);

void readFile(int& ladies, int& men, int& children, int& ladiesToRemove, int& menToRemove, int& childrenToRemove, char& stops);

void saveToFile(const std::vector < std::vector <char>>& vect, const char& stops);

void retrieveFile(const char& stops);

void displayVector(std::vector < std::vector <char>>& vect);

void generate(std::vector < std::vector <char>>& vect, int& ladies, int& men, int& children, int& ladiesToRemove, int& menToRemove, int& childrenToRemove, const char& stops);

void displaySafestPlan();


int main() {
	std::vector < std::vector <char>> vect
	{
		{' ', ' ', ' ', ' ', 'H'},

		{'-', '-', '-', '-'},
		{'-', '-', '-', '-'},
		{'-', '-', '-', '-'},
		{'-', '-', '-', '-'},

		{' ', ' ', ' ', ' ', 'H'},

		{'-', '-', '-', '-'},
		{'-', '-', '-', '-'},
		{'-', '-', '-', '-'},
		{'-', '-', '-', '-'},

		{' ', ' ', ' ', ' ', 'H'}
	};


	int ladies = 0;
	int children = 0;
	int men = 0;
	int ladiesToRemove = 0;
	int childrenToRemove = 0;
	int menToRemove = 0;
	char stops = 'a';

	displayRules(vect, ladies, men, children, ladiesToRemove, menToRemove, childrenToRemove, stops);

	return 0;
}

void displayRules(std::vector < std::vector <char>>& vect, int& ladies, int& men, int& children, int& ladiesToRemove, int& menToRemove, int& childrenToRemove, char& stops) {
	int input;
	bool flag = true;


	while (flag) {
		std::cout << "Welcome to the computer generated transport system!" << std::endl << std::endl;
		std::cout << "Before we start, few simple rules you must know: " << std::endl;
		std::cout << "H --> door" << std::endl;
		std::cout << "L --> Ladies" << std::endl;
		std::cout << "C --> Children" << std::endl;
		std::cout << "M --> Men" << std::endl << std::endl;
		std::cout << "In this seating plan program, a safe plan means no child can sit on column d, the most right seats!" << std::endl;
		std::cout << "With that out of the way, press 1 to continue" << std::endl << std::endl;
		std::cin >> input;
		if (input == 1)
		{
			menuSystem(vect, ladies, men, children, ladiesToRemove, menToRemove, childrenToRemove, stops);
			flag = false;
		}

		else
		{
			std::cout << "Invalid choice, please choose again!";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

}

void menuSystem(std::vector < std::vector <char>>& vect, int& ladies, int& men, int& children, int& ladiesToRemove, int& menToRemove, int& childrenToRemove, char& stops) {
	char input;
	bool flag = true;

	while (flag) {
		std::cout << "Press D to travel to the next stop!" << std::endl << std::endl;
		std::cout << "Press B to go back to the default plan!" << std::endl << std::endl;
		std::cout << "Press R to retrieve seating plans!" << std::endl << std::endl;
		std::cout << "Press S to display the safest sitting plan!" << std::endl << std::endl;
		std::cout << "Press Q to quit the program!" << std::endl << std::endl;

		std::cin >> input;

		switch (input) {
		case 'D':
		case 'd':
		{
			if (stops > 'e')
			{
				std::cout << "You have reached the end!";
				break;
			}

			readFile(ladies, men, children, ladiesToRemove, menToRemove, childrenToRemove, stops);
			generate(vect, ladies, men, children, ladiesToRemove, menToRemove, childrenToRemove, stops);
			std::cout << std::endl;
			stops += 1;

			break;
		}

		case 'B':
		case 'b':
		{
			displayDefaultPlan(vect, ladies, men, children, stops);
			break;
		}

		case 'R':
		case 'r':
		{
			bool quit = true;
			while (quit)
			{
				std::cout << std::endl;
				std::cout << "Press A to display stop A" << std::endl << std::endl;
				std::cout << "Press B to display stop B" << std::endl << std::endl;
				std::cout << "Press C to display stop C" << std::endl << std::endl;
				std::cout << "Press D to display stop D" << std::endl << std::endl;
				std::cout << "Press E to display stop E" << std::endl << std::endl;
				std::cout << "Press Q to go back to main menu" << std::endl << std::endl;

				char input;
				std::cin >> input;

				retrieveFile(input);

				if (input == 'Q' || input == 'q')
				{
					quit = false;
				}

			}
			break;
		}

		case 'S':
		case 's':
		{
		 displaySafestPlan();
		 break;
		}

		case 'Q':
		case 'q':
			std::cout << "You have quit the program!";
			flag = false;
			exit(0);

		default:
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Invalid choice entered, please try again!" << std::endl;
		}
		}
	}
}


void displayDefaultPlan(std::vector < std::vector <char>>& vect, int& ladies, int& men, int& children, char& stops) {
	ladies = 0;
	men = 0;
	children = 0;
	stops = 'a';
	bool deleteFile = true;
	char tempStop = 'a';

	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < vect[i].size(); j++)
		{
			if (i == 0 || i == 5 || i == 10)
			{
				continue;
			}
			vect[i][j] = '-';
		}
	}

	displayVector(vect);
	while (deleteFile) {
		std::ofstream ofs;
		std::string fileName = "save.txt";

		fileName.insert(4, 1, tempStop);
		ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
		tempStop += 1;

		ofs.close();

		if (tempStop > 'e') {
			deleteFile = false;
		}
	}
}

void readFile(int& ladies, int& men, int& children, int& ladiesToRemove, int& menToRemove, int& childrenToRemove, char& stops) {
	std::ifstream read;
	std::string fileName = "stop";

	fileName += stops;
	fileName.append(".txt");

	read.open(fileName);
	std::string fileContent;

	while (getline(read, fileContent))
	{
		if (fileContent[0] == 'L') {
			ladies = fileContent[1] - '0';
		}

		if (fileContent[0] == 'M') {
			men = fileContent[1] - '0';
		}

		if (fileContent[0] == 'C') {
			children = fileContent[1] - '0';
		}

		if (fileContent[0] == 'F') {
			ladies = fileContent[1] - '0';
			children = (fileContent[1] - '0') * 2 ;
		}
															//FILE CONTENT MUST BE INSERTED IN SPECIFIC WAY
															//CHECK TEXT FILES ALREADY MADE TO SEE HOW 
		if (fileContent.size() > 2) {

			if (fileContent[1] == 'L') {
				ladiesToRemove = fileContent[2] - '0';
			}

			if (fileContent[1] == 'M') {
				menToRemove = fileContent[2] - '0';
			}

			if (fileContent[1] == 'C') {
				childrenToRemove = fileContent[2] - '0';
			}

			if (fileContent[1] == 'F') {
				ladiesToRemove = fileContent[2] - '0';
				childrenToRemove = (fileContent[2] - '0') * 2;
			}
		}
	}
	read.close();
}

void saveToFile(const std::vector < std::vector <char>>& vect, const char& stops) {
	std::ofstream save;
	std::string fileName = "save.txt";
	fileName.insert(4, 1, stops);

	save.open(fileName);
	for (int r = 0; r < vect.size(); r++)
	{
		for (int c = 0; c < vect[r].size(); c++)
		{
			save << vect[r][c] << ',';
		}

		save << '\n';
	}
	save.close();
}

void retrieveFile(const char& stops) {

	std::cout << "\nRetrieving stop: " << stops << std::endl;

	std::ifstream retrieve;
	std::string fileName = "save.txt";
	fileName.insert(4, 1, stops);
	std::string storeFile;

	retrieve.open(fileName);
	while (getline(retrieve, storeFile)) {
		std::stringstream ss(storeFile);
		std::string pass;

		while (getline(ss, pass, ',')) {
			std::cout << pass << " ";
		}
		std::cout << std::endl;
	}
	retrieve.close();
}

//GENERIC VECTOR DISPLAY FUNCTION
void displayVector(std::vector < std::vector <char>>& vect) {
	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < vect[i].size(); j++)
		{
			std::cout << vect[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void generate(std::vector<std::vector<char>>& vect, int& ladies, int& men, int& children, int& ladiesToRemove, int& menToRemove, int& childrenToRemove, const char& stops)
{
	std::cout << "Stop: " << stops << std::endl;

	// ADDING WOMEN
	for (int r = 0; r < vect.size(); r++)
	{
		for (int c = 0; c < vect[r].size(); c++)
		{
			if (vect[r][c] == '-' && ladies > 0)
			{
				vect[r][c] = 'L';
				ladies--;
			}
		}
	}

	// WOMEN COULDNT BE ADDED
	for (int i = 0; i < ladies; i++)
	{
		std::cout << "\nLady couldn't be added" << std::endl;
	}

	// ADDING MEN
	for (int r = 6; r < vect.size(); r++)
	{
		for (int c = 0; c < vect[r].size(); c++)
		{
			if (vect[r][c] == '-' && men > 0)
			{
				vect[r][c] = 'M';
				men--;
			}

		}
	}

	// MEN COULDNT BE ADDED
	for (int i = 0; i < men; i++)
	{
		std::cout << "\nMan couldn't be added" << std::endl;
	}

	for (int r = 0; r < vect.size(); r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (vect[r][c] == '-' && children > 0)
			{
				vect[r][c] = 'C';
				children--;
			}
		}
	}

	for (int r = 0; r < vect.size(); r++)
	{
		for (int c = 0; c < vect[r].size(); c++)
		{
			if (vect[r][c] == 'L' && ladiesToRemove > 0)
			{
				vect[r][c] = '-';
				ladiesToRemove--;
			}
			if (vect[r][c] == 'M' && menToRemove > 0)
			{
				vect[r][c] = '-';
				menToRemove--;
			}
			if (vect[r][c] == 'C' && childrenToRemove > 0)
			{
				vect[r][c] = '-';
				childrenToRemove--;
			}
		}
	}

	displayVector(vect);
	saveToFile(vect, stops);
}

void displaySafestPlan() {
	 std::vector < std::vector <char>> vect{
		 {' ', ' ', ' ', ' ', 'H'},

		 {'-', '-', 'L', 'L'},
		 {'L', 'L', '-', 'L'},
		 {'-', '-', '-', 'L'},
		 {'C', 'C', 'L', 'L'},

		 {' ', ' ', ' ', ' ', 'H'},

	 	 {'M', 'M', 'M', 'M'},
		 {'M', 'M', 'M', 'M'},
		 {'M', 'M', 'M', 'M'},
		 {'M', 'M', 'M', 'M'},

		 {' ', ' ', ' ', ' ', 'H'}
	 };
	 std::cout << "Safest Plan: " << std::endl << std::endl;
	 for (int i = 0; i < vect.size(); i++)
	 {
		 for (int j = 0; j < vect[i].size(); j++)
		 {
			 std::cout << vect[i][j] << " ";
		 }
		 std::cout << std::endl;
	 }
	 std::cout << std::endl;
	 std::cout << std::endl;
}
