//Assignment 2 - Linked Lists & Stacks
//Credit: ChatGPT - Data File, Logic refinement

#include "Functions.h"

int main()
{
	// Intro
	Intro();

	// Declare your linked lists
	Single_Linked_List studentList;
	Stack dropStack;

	// Read Data
	ifstream inFile("DataFile.txt");
	if (!inFile.good()) {
		cerr << "Error opening file." << endl;
		return 1;
	}
	readFile(inFile, studentList, dropStack);


	// Menu
	menu(studentList, dropStack); 

	// Write Data
	writeFile(studentList, dropStack);

	return 0;
}
