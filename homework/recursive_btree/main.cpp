#include <iostream>
#include <string>
using namespace std;

struct Tree {
    int value;
    Tree* left;
    Tree* right;
};

Tree * insert(Tree* C, int data) {
    if (C == NULL) {
        C = new Tree;
        C -> value = data;
        C -> left = NULL;
        C -> right = NULL;
    }
    else if (data < C -> value) {
        C->left = insert(C -> left, data);
    }
    else {
        C->right = insert(C-> right, data);
    }
    return C;
}

void print(Tree* C) {
    if (C == NULL) return;
    print(C->left);
    cout << C->value << ", ";
    print(C->right);
}

int count(Tree* C) {
    if (C == NULL) return 0;
    return 1 + count(C->left) + count(C->right);    
}

bool isMember(Tree* C, int key) {
    if (C == NULL) return false;
    if (C -> value == key) return true;
    return isMember(C->left, key) || isMember(C->right, key);
}

int main(){
    Tree* root = NULL;
    string input;
    cout << "Input numbers, end with empty line" << endl;
    cout << "Input a number: ";
    while (getline(cin, input)) {
        if (input.empty()) {
            break;
        }
        root = insert(root, stoi(input));
        cout << "Input a number: ";
    }
    cout << "Current dataset: ";
    print(root);
    cout << endl;
    cout << "Total number of nodes: " << count(root) << endl;
    cout << "Search for a node by value: ";
    cin >> input;
    cout << "Result: " << isMember(root, stoi(input)) << endl;
    cout << "finished" << endl;
    cin.get();
    cin.get();
    return 0;
}