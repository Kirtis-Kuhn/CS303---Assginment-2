#include "SingleList.h"

//Initalizer
Single_Linked_List::Single_Linked_List() : head(nullptr), tail(nullptr), num_items(0) {}

//Destructor
Single_Linked_List::~Single_Linked_List() {
    clear();
}

void Single_Linked_List::clear() {
    while (head) {
		Node* temp = head; // Store current head
		head = head->next; // Move head to next node
        delete temp->student; // free Students object
        delete temp;          // free Node
    }
    tail = nullptr;
    num_items = 0;
}

void Single_Linked_List::push_back(Students* s) {
    Node* newNode = new Node(s);
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    num_items++;
}

void Single_Linked_List::push_front(Students* s) {
    Node* newNode = new Node(s);
    if (!head) {
        head = tail = newNode;
    }
    else {
		newNode->next = head; // Shift new node to current head
		head = newNode;     // Update head to new node
    }
    num_items++;
}

void Single_Linked_List::pop_back() {
    if (!head) return;
	if (head == tail) { // Only one element in the list
		delete head->student; // Free the Students object
		delete head; // Free the Node
        head = tail = nullptr;
    }
    else {
        Node* current = head;
		while (current->next != tail) { // Traverse to the second last node
            current = current->next;
        }
        delete tail->student;
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    num_items--;
}

void Single_Linked_List::pop_front() {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    delete temp->student;
    delete temp;
    if (!head) tail = nullptr;
    num_items--;
}

Students* Single_Linked_List::front() {
    return head ? head->student : nullptr;
}

Students* Single_Linked_List::back() {
    return tail ? tail->student : nullptr;
}

bool Single_Linked_List::empty() const {
    return num_items == 0;
}

//Accepts an index 
//Returns the student AT that index
Students* Single_Linked_List::getAt(size_t index) const {
    Node* current = head;
    size_t count = 0;

    while (current != nullptr) {   
        if (count == index) {
            return current->student;
        }
        current = current->next;
        count++;
    }

    return nullptr;
}


void Single_Linked_List::display() const {
    Node* current = head;
    while (current) {
        Students* s = current->student;
        cout << "ID: " << s->getId()
            << ", Status: " << s->getStatus()
            << ", Name: " << s->getFirstName() << " " << s->getLastName()
            << ", GPA: " << fixed << setprecision(2) << s->getGpa() << endl;
        current = current->next;
    }
    cout << "Total Students: " << num_items << endl;
}

//Accepts index and Students pointer
void Single_Linked_List::insert(size_t index, Students* s) {
	if (index == 0) { // Insert at the front
        push_front(s);
        return;
    }
	if (index >= num_items) { // Insert at the back
        push_back(s);
        return;
    }

    Node* newNode = new Node(s);
    Node* current = head;
	for (size_t i = 0; i < index - 1; ++i) { //Search for the node before the index
        current = current->next;
    }
	newNode->next = current->next; // Link new node to the next node
	current->next = newNode; // Link previous node to new node
    num_items++;
}

bool Single_Linked_List::remove(size_t index) {
	if (index >= num_items) return false;   // Invalid index
	if (index == 0) { // Remove from the front
        pop_front();
        return true;
    }

    Node* current = head;
    for (size_t i = 0; i < index - 1; ++i) {
        current = current->next;
    }

	Node* target = current->next; // Node to be removed
	current->next = target->next; // Link previous node to the next node
	if (target == tail) tail = current; // Update tail if removing the last node
    delete target->student;
    delete target;
    num_items--;
    return true;
}

size_t Single_Linked_List::find(int id) const {
    Node* current = head;
    size_t index = 0;
    while (current) {
        if (current->student->getId() == id) return index;
        current = current->next;
        index++;
    }
    return -1; // Not found
}
