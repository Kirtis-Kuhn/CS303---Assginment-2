#pragma once
#include "SingleList.h"
#include "Stack.h"

//Display Context
void Intro();

//Menu functions (Accepts Linked List and Stack)
void menu(Single_Linked_List& studentList, Stack& dropStack);
void menuDrop(Single_Linked_List& studentList, Stack& dropStack);
void menuStudent(Single_Linked_List& studentList, Stack& dropStack);

//Drop menu functions
void addToStack(Single_Linked_List& studentList, Stack& dropStack);
void readmitFromStack(Single_Linked_List& studentList, Stack& dropStack);
void removeFromStack(Single_Linked_List& studentList, Stack& dropStack);

//Student menu functions
bool addStudent(Single_Linked_List& studentList);
bool removeStudent(Single_Linked_List& studentList);

// Utility functions
bool isDigit(const string& num);
bool isID(const string& num);
string toUpper(const string& str);
void readFile(ifstream& in, Single_Linked_List& list, Stack& dropStack);
void writeFile(const Single_Linked_List& studentList, const Stack& dropStack);
