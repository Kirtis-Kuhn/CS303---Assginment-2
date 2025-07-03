#include "Stack.h"

Stack::Stack() {}

bool Stack::isEmpty() const {
    return stack.empty();
}

void Stack::push(Students* value) {
    stack.push_back(value);
}

void Stack::pop() {
    if (!isEmpty()) {
        stack.pop_back();
    }
    else {
        cout << "Stack is empty. Cannot pop.\n";
    }
}

Students* Stack::top() const {
    if (!isEmpty()) {
        return stack.back();
    }
    else {
        cout << "Stack is empty.\n";
        return nullptr; 
    }
}

double Stack::average() const {
    if (isEmpty()) return 0.0;

    double sum = 0.0;
    for (Students* s : stack) {
        sum += s->getGpa();
    }
    return sum / stack.size();
}

void Stack::display() const {
    cout << "\nStack elements (top to bottom):\n";
    if (stack.empty()) {
        cout << "  [Stack is empty]" << endl;
        return;
    }

    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
        Students* s = *it;
        cout << "  ID: " << s->getId()
            << ", Name: " << s->getFirstName() << " " << s->getLastName()
            << ", GPA: " << fixed << setprecision(2) << s->getGpa()
            << endl;
    }
}
