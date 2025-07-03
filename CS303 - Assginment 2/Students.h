#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <numeric>

using namespace std;

struct Data{
	int id; // Numeric ID
	char status; // 'C' for current, 'D' for dropped, 'P' for probation
	string firstName;
	string lastName;
	float gpa;
};

class Students {
private:
	int id;
	char status;
	string firstName;
	string lastName;
	float gpa;

public:
	// Default constructor
	Students() : id(0), status(' '), firstName(""), lastName(""), gpa(0.0f) {}

	// Overloaded constructor
	Students(int id, char status, string firstName, string lastName, float gpa)
		: id(id), gpa(gpa) {
		this->id = id;
		this->status = status;
		this->firstName = firstName;
		this->lastName = lastName;
		this->gpa = gpa;
	}

	// Getters
	int getId() const { return id; }
	char getStatus() const { return status; }
	string getFirstName() const { return firstName; }
	string getLastName() const { return lastName; }
	float getGpa() const { return gpa; }

	// Setters
	void setId(int id) { this->id = id; }
	void setStatus(char status) { this->status = status; }
	void setFirstName(const string& firstName) { this->firstName = firstName; }
	void setLastName(const string& lastName) { this->lastName = lastName; }
	void setGpa(float gpa) { this->gpa = gpa; }

};

