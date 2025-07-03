#include "Functions.h"


//Utility Functions
bool isDigit(const string& num) {
	return num.find_first_not_of("0123456789.") == string::npos;
}

bool isID(const string& num) {
	return num.find_first_not_of("0123456789") == string::npos;
}

string toUpper(const string& str) {
	string result = str;
	for (char& c : result) c = toupper(c);
	return result;
}


void Intro() {
	string formatTN = "Intro";
	int formatTitle = (100 - formatTN.size()) / 2;

	cout << endl << string(formatTitle, ' ') << formatTN << endl;
	cout << string(100, '~') << endl;

	cout << "Welcome to the Assistant Accedimic Advising Senario!" << endl;
	cout << "This program is used by the Head Accedemic Advisor to track their Current and Dropped students." << endl << endl;

	cout << "There will also be a list of students who have been dropped." << endl;
	cout << "The program will allow you to add, remove, and display all students." << endl;
	cout << "Credit: ChatGPT Data File" << endl;
	
	cout << string(100, '~') << endl;
}

void readFile(ifstream& in, Single_Linked_List& list, Stack& dropStack) {

	//Error handling File
	ofstream err("error_log.txt");
	if (!err.good() || !in.is_open()) {
		cout << "Error opening file(s)." << endl;
		return;
	}


	// Read each line from the file
	string line, token;
	while (getline(in, line)) {
		stringstream ss(line);
		vector<string> tokens;
		while (getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		try {
			if (tokens.size() < 5) throw runtime_error("Insufficient data in line");
			if (!isDigit(tokens[0])) throw runtime_error("ID must be a digit");

			int id = stoi(tokens[0]);
			char status = tokens[1][0];
			string firstName = tokens[2];
			string lastName = tokens[3];

			if (!isDigit(tokens[4])) throw runtime_error("GPA must be a digit");
			float gpa = stof(tokens[4]);

			Students* newStudent = new Students(id, status, firstName, lastName, gpa);

			//Vaildate ID uniqueness
			if (list.find(id) != static_cast<size_t>(-1)) {
				throw runtime_error("ID already taken in student list");
			}

			for (Students* s : dropStack.getRawStack()) {
				if (s->getId() == id) {
					throw runtime_error("ID already taken in drop stack");
				}
			}

			// Add to the appropriate list or stack
			if (toupper(status) == 'D') {
				dropStack.push(newStudent);
			}
			else {
				list.push_back(newStudent);
			}
		}
		catch (const runtime_error& e) {
			// Log the error to the error file
			err << "Error: " << line << " - " << e.what() << endl;
			continue;
		}
	}

	in.close();
	cout << "Data loaded successfully into memory." << endl;
}


//Menu Functions
void menu(Single_Linked_List& studentList, Stack& dropStack){
	string choice;
	string formatTN = "Main Menu";
	int formatTitle = (100 - formatTN.size()) / 2;
	vector<string> vChoices = { "Drop List Menu", "Student Menu", "Exit Program" };

	//Format and Display Menu
	cout << endl << string(formatTitle, ' ') << formatTN << endl;
	cout << string(100, '=') << endl;

	for (int i = 0; i < vChoices.size(); i++) {
		cout << setw(2) << i + 1 << ") " << vChoices[i] << endl;
	}

	//Choice Input
	cout << string(100, '=') << endl;
	cout << "Enter your choice (int): ";
	cin >> choice;
	while (!isDigit(choice)) {
		cout << "Invalid input. Please enter a valid integer: ";
		cin.clear();
		cin >> choice;
	}

	int choiceInt = stoi(choice);

	//Check for Exit
	if (choiceInt == vChoices.size()) {
		cout << "Exiting Program..." << endl << endl;
		return;
	}
	//Check for Valid Choice
	else if (choiceInt < 1 || choiceInt > vChoices.size()) {
		cout << "Invalid choice. Please try again." << endl;
		menu(studentList, dropStack);
	}
	else {
		switch (choiceInt) {
		case 1: // Drop List Menu
			menuDrop(studentList, dropStack);
			break;
		case 2: // Student Menu
			menuStudent(studentList, dropStack);
			break;
		default: //Loop Until Valid Choice
			cout << "Invalid choice. Please try again." << endl << endl;
			menu(studentList, dropStack);
		}
	}
}

void menuDrop(Single_Linked_List& studentList, Stack& dropStack){

	//Drop Menu Intro because Senario doesnt make sense > but still went with it
	cout << endl << string(100, '~') << endl;
	cout << "Welcome to the Dropped Student Menu!" << endl;
	cout << "This functionality is very strange. This is because students who are dropped must wait, " << endl;
	cout << "until every student that has dropped more recently gets re-admitted first." << endl;
	cout << "If Sue dropped, then Bob dropped, then Alice dropped, Sue would have to wait for Bob,\n and Bob would wait for Alice." << endl;
	cout << string(100, '~') << endl << endl;

	string choice;
	string formatTN = "Dropped Student Menu";
	int formatTitle = (100 - formatTN.size()) / 2;
	vector<string> vChoices = { "Add Dropped Student", "Display Dropped Students", "Display First in line Dropped",
								"Re-admit Student", "Remove Dropped Student", "Return to Main Menu" 
	};

	//Format and Display Menu
	cout << endl << string(formatTitle, ' ') << formatTN << endl;
	cout << string(100, '-') << endl;

	for (int i = 0; i < vChoices.size(); i++) {
		cout << setw(2) << i + 1 << ") " << vChoices[i] << endl;
	}

	//Choice Input
	cout << string(100, '-') << endl;
	cout << "Enter your choice (int): ";
	cin >> choice;
	while (!isDigit(choice)) {
		cout << "Invalid input. Please enter a valid integer: ";
		cin.clear();
		cin >> choice;
		cout << endl;
	}

	int choiceInt = stoi(choice);

	//Check for Exit
	if (choiceInt == vChoices.size()) {
		cout << "Exiting Dropped menu..." << endl << endl;
		menu(studentList, dropStack); // Return to main menu
	}
	//Check for Valid Choice
	else if (choiceInt < 1 || choiceInt > vChoices.size()) {
		cout << "Invalid choice. Please try again." << endl;
		menuDrop(studentList, dropStack);
	}
	else {
		switch (choiceInt) {
		case 1: { //Add Dropped Student
			addToStack(studentList, dropStack);
			break;
		}
		case 2: { //Display Dropped Students
			dropStack.display();
			break;
		}
		case 3: { //Display First in line Dropped
			displayFirstDropped(dropStack);
			break;
		}
		case 4:{ //Re-admit Student
			readmitFromStack(studentList, dropStack);
			break;
		}
		case 5:
			removeFromStack(studentList, dropStack);
			break;
		default:
			cout << "Invalid choice. Please try again." << endl << endl;
			break;
		}
		menuDrop(studentList, dropStack);
	}
}

void addToStack(Single_Linked_List& studentList, Stack& dropStack) {
	if (studentList.empty()) {
		cout << "No students available to drop." << endl << endl;
		return;
	}

	// Display current students
	cout << "\nCurrent Students:\n";
	studentList.display();
	cout << endl;

	string input;
	cout << "Enter the ID of the student to drop (or type 'exit' to cancel): ";
	cin >> input;

	if (toUpper(input) == "EXIT" || toUpper(input) == "QUIT") {
		cout << "Exiting drop operation.\n" << endl;
		return;
	}

	if (!isID(input)) {
		cout << "Invalid ID format. Please enter a valid integer ID.\n";
		return;
	}

	int id = stoi(input);
	size_t index = studentList.find(id);
	if (index == static_cast<size_t>(-1)) {
		cout << "Student with ID " << id << " not found.\n" << endl;
		return;
	}

	Students* student = studentList.getAt(index);
	if (!student) {
		cout << "Error retrieving student.\n";
		return;
	}

	// Create a deep copy and update its status
	Students* droppedStudent = new Students(*student);
	droppedStudent->setStatus('D');

	// Push copy to drop stack
	dropStack.push(droppedStudent);

	// Remove original from student list
	studentList.remove(index);

	cout << "Student with ID " << id << " has been dropped and added to the stack.\n";

	menuDrop(studentList, dropStack);
}

void displayFirstDropped(const Stack& dropStack) {
	if (dropStack.isEmpty()) {
		cout << "No students in drop stack." << endl << endl;
		return;
	}

	Students* topStudent = dropStack.top();
	cout << "\nNext to be re-admitted: "
		<< topStudent->getFirstName() << " "
		<< topStudent->getLastName()
		<< " (GPA: " << fixed << setprecision(2) << topStudent->getGpa() << ")" << endl << endl;
}


void readmitFromStack(Single_Linked_List& studentList, Stack& dropStack) {
	// Check if drop stack is empty
	if (dropStack.isEmpty()) {
		cout << "No students in drop stack." << endl << endl;
		return;
	}

	Students* topStudent = dropStack.top();
	cout << "Next to be re-admitted: "
		<< topStudent->getFirstName() << " "
		<< topStudent->getLastName()
		<< " (GPA: " << fixed << setprecision(2) << topStudent->getGpa() << ")" << endl;

	string input;
	cout << "Would you like to re-admit this student? (yes/no): ";
	cin >> input;

	if (toUpper(input) == "YES" || toUpper(input) == "Y") {
		Students* reAdmitted = new Students(*topStudent); // Deep copy
		reAdmitted->setStatus('C'); // Mark as current
		studentList.push_back(reAdmitted);
		dropStack.pop();
		cout << "Student has been re-admitted.\n";
	}
	else {
		cout << "Re-admission cancelled.\n";
	}
}


void removeFromStack(Single_Linked_List& studentList, Stack& dropStack) {
	// Check if drop stack is empty
	if (dropStack.isEmpty()) {
		cout << "No students in drop stack to remove." << endl << endl;
		return;
	}

	Students* topStudent = dropStack.top(); //Get the top student from the drop stack
	cout << "\nTop student in drop stack:\n";
	cout << "ID: " << topStudent->getId()
		<< ", Name: " << topStudent->getFirstName() << " " << topStudent->getLastName()
		<< ", GPA: " << fixed << setprecision(2) << topStudent->getGpa() << endl;


	cout << endl;

	string input;
	cout << "Remove this student? (yes/no): ";
	cin >> input;

	if (toUpper(input) == "YES" || toUpper(input) == "Y") {
		dropStack.pop(); // Remove from drop stack
		cout << "Student removed from drop stack.\n" << endl;
	}
	else {
		cout << "Removal cancelled.\n" << endl;
	}
	menuDrop(studentList, dropStack); // Return to drop menu
}



void menuStudent(Single_Linked_List& studentList, Stack& dropStack) {
	string choice;
	string formatTN = "Student Menu";
	int formatTitle = (100 - formatTN.size()) / 2;
	vector<string> vChoices = { "Add Student", "Display Students", "Remove Student",
								"Return to Main Menu"
	};

	//Format and Display Menu
	cout << endl << string(formatTitle, ' ') << formatTN << endl;
	cout << string(100, '-') << endl;
		
		for(int i = 0; i < vChoices.size(); i++) {
			cout << setw(2) << i + 1 << ") " << vChoices[i] << endl;
		}


		//Choice Input
		cout << string(100, '-') << endl;
		cout << "Enter your choice (int): ";
		cin >> choice;
		while (!isDigit(choice)) {
			cout << "Invalid input. Please enter a valid integer: ";
			cin.clear();
			cin >> choice;
			cout << endl;
		}

		int choiceInt = stoi(choice);

		//Check for Exit
		if(choiceInt == vChoices.size()) {
			cout << "Exiting Student menu..." << endl << endl;
			menu(studentList, dropStack);
		} 
		//Check for Valid Choice
		else if (choiceInt < 1 || choiceInt > vChoices.size()) {
			cout << "Invalid choice. Please try again." << endl << endl;
			menuStudent(studentList, dropStack);
		} 
		else {
			switch (choiceInt) {
			case 1: // Add Student
					addStudent(studentList);
					break;
			case 2: // Display Students
					studentList.display();
					break;
			case 3: // Remove Student
					removeStudent(studentList);
					break;
			default: // Loop Until Valid Choice
					cout << "Invalid choice. Please try again." << endl;
			}
			menuStudent(studentList, dropStack); //Loop After Input
		}
}

bool addStudent(Single_Linked_List& studentList) {
	vector<string> fields = { "ID", "Status (C/P)", "First Name", "Last Name", "GPA" };
	vector<string> inputs(5);
	bool success = true;

	for (size_t i = 0; i < fields.size(); i++) {
		bool isValid = false;
		while (!isValid) {
			cout << "Enter " << fields[i] << " (or type 'exit'): ";
			string input;
			cin >> input;
			string check = toUpper(input);
			cout << endl;

			if (check == "EXIT" || check == "QUIT") {
				cout << "Exiting student addition...\n";
				return false;
			}

			switch (i) {
			case 0: { // ID
				if (!isDigit(input)) {
					cout << "Error: ID must be an integer.\n";
					break;
				}
				int id = stoi(input);
				if (studentList.find(id) != -1) {
					cout << "Error: ID already exists.\n";
					isValid = false;
					break;
				}
				isValid = true;
				break;
			}
			case 1: { // Status
				if (isalpha(input[0]) && input.length() == 1) {
					input = toUpper(input); // missing semicolon
					if (input != "C" && input != "P") {
						cout << "Error: Status must be 'C' or 'P'.\n";
					}
					else {
						isValid = true;
					}
				}
				else {
					cout << "Error: Status must be a single letter.\n" << endl;
					isValid = false;
				}
				break;
			}
			case 4: { // GPA
				if (!isDigit(input)) {
					cout << "Error: GPA must be a digit.\n" << endl;
					isValid = false;
				}
				else if(stof(input)<0 || stof(input)>4.0) {
					cout << "Error: GPA must be between 0.0 and 4.0.\n" << endl;
					isValid = false;
				}
				else {
					isValid = true;
				}
				break;
			}
			default: { // First Name, Last Name
				if (input.empty()) {
					cout << "Error: " << fields[i] << " cannot be empty.\n" << endl;
				}
				else {
					isValid = true;
				}
				break;
			}
			}

			if (isValid) inputs[i] = input;
		}
	}

	// Build and insert student
	int id = stoi(inputs[0]);
	char status = inputs[1][0];
	string firstName = inputs[2];
	string lastName = inputs[3];
	float gpa = stof(inputs[4]);

	Students* newStudent = new Students(id, status, firstName, lastName, gpa);
		studentList.push_back(newStudent);

	cout << " Student added successfully.\n";
	return true;
}

bool removeStudent(Single_Linked_List& studentList) {
	// Check if the student list is empty
	if (studentList.empty()) {
		cout << "No students available to remove." << endl;
		return false;
	}

	vector<string> removeOptions = { "Remove by ID", "Remove by First and Last Name" };
	string input;
	bool isValid = false;

	cout << "\nHow would you like to remove the student?\n";
	for (size_t i = 0; i < removeOptions.size(); i++) {
		cout << " " << i + 1 << ") " << removeOptions[i] << endl;
	}

	while (!isValid) {
		cout << "Enter your choice (or type 'exit'): ";
		cin >> input;
		string lower = toUpper(input);
		cout << endl << endl;

		if (lower == "EXIT" || lower == "QUIT") return false;

		if (input == "1") {
			// === Remove by ID ===
			while (true) {
				cout << "Enter student ID to remove (or 'exit'): ";
				cin >> input;
				if (toUpper(input) == "EXIT") return false;

				if (!isDigit(input)) {
					cout << "Error: ID must be a number.\n";
					continue;
				}

				cout << endl;
				int id = stoi(input);
				size_t index = studentList.find(id); // Find the index of the student with the given ID

				if (index != static_cast<size_t>(-1)) { // If the student is found
					studentList.remove(index);
					cout << "Student removed from student list.\n\n";
					return true;
				}

				cout << "No student with ID " << id << " found.\n"; //else Case
				return false;
			}
		}

		else if (input == "2") {
			// === Remove by Name ===
			string firstName, lastName;
			cout << "Enter First Name (or 'exit'): ";
			cin >> firstName;
			if (toUpper(firstName) == "EXIT") return false;

			cout << endl;

			cout << "Enter Last Name (or 'exit'): ";
			cin >> lastName;
			if (toUpper(lastName) == "EXIT") return false;

			cout << endl;

			//Initialize search variables
			size_t index = 0;
			bool found = false;
			Single_Linked_List::Node* cur = studentList.getHead();

			// Search through the student list
			while (cur) {
				if (toUpper(cur->student->getFirstName()) == toUpper(firstName) &&
					toUpper(cur->student->getLastName()) == toUpper(lastName)) {
					studentList.remove(index);
					cout << "Removed from student list.\n";
					return true;
				}
				cur = cur->next;
				index++;
			}

			cout << "Student not found.\n"; //Else Case
			return false;
		}

		else {
			cout << "Invalid input. Choose 1 or 2.\n" << endl;
		}
	}

	return false;
}

void writeFile(const Single_Linked_List& studentList, const Stack& dropStack) {
	ofstream out("student_output.csv");
	if (!out.is_open()) {
		cout << "Error opening output file." << endl;
		return;
	}

	// Write from student list
	Single_Linked_List::Node* current = studentList.getHead();
	while (current != nullptr) {
		Students* s = current->student;
		out << s->getId() << ","
			<< s->getStatus() << ","
			<< s->getFirstName() << ","
			<< s->getLastName() << ","
			<< fixed << setprecision(2) << s->getGpa()
			<< endl;
		current = current->next;
	}

	// Write from drop stack (top to bottom, newest to oldest)
	Stack temp = dropStack;
	while (!temp.isEmpty()) {
		Students* s = temp.top();
		out << s->getId() << ","
			<< s->getStatus() << ","
			<< s->getFirstName() << ","
			<< s->getLastName() << ","
			<< fixed << setprecision(2) << s->getGpa()
			<< endl;
		temp.pop();
	}

	out.close();
	cout << "Student data written to 'student_output.csv'.\n";
}



