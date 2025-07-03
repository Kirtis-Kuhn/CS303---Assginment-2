#pragma once
#include <vector>
#include <iostream>
#include <numeric>
#include "Students.h"

using namespace std;

class Stack {
private:
    vector<Students*> stack;

public:
    Stack();

    bool isEmpty() const;
    void push(Students* value);
    void pop();
    Students* top() const;
    double average() const;
	vector<Students*> getRawStack() const { return stack; } 

    void display() const;
};

