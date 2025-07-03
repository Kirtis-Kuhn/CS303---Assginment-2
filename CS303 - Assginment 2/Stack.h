#pragma once

#include "Students.h"

using namespace std;

class Stack {
private:
    vector<Students*> stack;

public:
    Stack();

    //Edit Funcitons
    void push(Students* value);
    void pop();

	// Access Functions
    bool isEmpty() const;
    Students* top() const;
    double average() const;
	vector<Students*> getRawStack() const { return stack; } 

    void display() const;
};

