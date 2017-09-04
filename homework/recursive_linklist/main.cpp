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
    if (current == nullptr) {
        current = new Node;
        current -> value = data;
        current -> next = nullptr;
        return current;
    }
    else current -> next = append(current->next, data);
}

Node * insert(Node* current, int data) {
    if (current == nullptr) {
        current = new Node;
        current -> value = data;
        current -> next = nullptr;
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

//reverse link list by splitting list in two and running reverse again on the remaining nodes
Node * reverse(Node* C) {
    if (C == nullptr) return nullptr;
    if (C->next == nullptr) return C;
    Node* remaining = reverse(C->next);
    C->next->next = C;
    C->next = nullptr; //Treat current node as if it was the last node
    return remaining;
}

void print(Node* current) {
    if (current == nullptr) {
        return;
    }
    else {
        cout << current -> value << ", ";
        return print(current->next);
    }
}

int sum(Node* current) {
    if (current -> next == nullptr) {
        return current -> value;
    }
    else return current -> value + sum(current -> next);
}

int main() {
    Node* lst1 = nullptr;
    string input;
    cout << "Input numbers, end with empty line" << endl;
    cout << "Input a number: ";
    while (getline(cin, input)) {
        if (input.empty()) {
            break;
        }
        lst1 = append(lst1, stoi(input));
        cout << "Input a number: ";
    }
    cout << "Current dataset: ";
    print(lst1);
    lst1 = reverse(lst1);
    cout << endl << "Reversed dataset: ";
    print(lst1);

    cout << endl << "finished" << endl;
    return 0;
}

