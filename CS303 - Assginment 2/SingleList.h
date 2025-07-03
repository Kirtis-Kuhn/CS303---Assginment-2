#pragma once

#include "Students.h"

class Single_Linked_List {

public:
    struct Node {
        Students* student;
        Node* next;

        Node(Students* s) : student(s), next(nullptr) {}
    };
    Single_Linked_List();
    ~Single_Linked_List();

    //Edit Functions
    void push_front(Students* s);
    void push_back(Students* s);
    void pop_front();
    void pop_back();
    void insert(size_t index, Students* s);
    bool remove(size_t index);

	// Access Functions
    Students* front();
    Students* back();
    bool empty() const;
    Students* getAt(size_t index) const;
    size_t find(int id) const;
    void display() const;
    Node* getHead() const { return head; }


private:
    void clear(); 
    Node* head;
    Node* tail;
    size_t num_items; // Deletes all nodes and student objects
};
