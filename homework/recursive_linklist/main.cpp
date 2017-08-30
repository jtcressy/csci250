// Joel Cressy - Homework 8/30/17
// Recursive singly-linked list operations
#include <iostream>
#include <string>
using namespace std;

struct Node {
    int value;
    Node* next;
};

Node * append(Node* current, int data) {
    if (current == NULL) {
        current = new Node;
        current -> value = data;
        current -> next = NULL;
        return current;
    }
    else current -> next = append(current->next, data);
}

Node * insert(Node* current, int data) {
    if (current == NULL) {
        current = new Node;
        current -> value = data;
        current -> next = NULL;
        return current;
    }
    else if (data > current -> value) {
        Node* insert = new Node;
        insert -> value = data;
        insert -> next = current;
        return insert;
    }
    else current -> next = insert(current -> next, data);
}

Node * del(Node* current, int data) {
    if (current -> value == data) {
        Node* next = current -> next;
        delete current;
        return next;
    }
    else current -> next = del(current -> next, data);
}

void print(Node* current) {
    if (current == NULL) {
        return;
    }
    else {
        cout << current -> value << ", ";
        return print(current->next);
    }
}

int sum(Node* current) {
    if (current -> next == NULL) {
        return current -> value;
    }
    else return current -> value + sum(current -> next);
}

int main() {
    Node* head = NULL;
    string input;
    cout << "Input numbers, end with empty line" << endl;
    cout << "Input a number: ";
    while (getline(cin, input)) {
        if (input.empty()) {
            break;
        }
        head = append(head, stoi(input));
        cout << "Input a number: ";
    }
    cout << "Current dataset: ";
    print(head);
    cout << endl;
    cout << "Sum of all integers: " << sum(head) << endl;
    cout << "Delete a number: ";
    cin >> input;
    if (input.empty()) {
        cout << "No number to delete, continuing..." << endl;
    }
    else {
        head = del(head, stoi(input));
        cout << "Deleted first instance of " << input << ":" << endl;
        print(head);
        cout << endl;
    }
    cout << "Enter a number to insert: ";
    cin >> input;
    if (input.empty()) {
        cout << "No number to insert, continuing..." << endl;
    }
    else {
        head = insert(head, stoi(input));
        cout << "Inserted " << input << ":" << endl;
        print(head);
        cout << endl;
    }
    cout << "finished" << endl;
    return 0;
}

