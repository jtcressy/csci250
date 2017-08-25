#include <iostream>
using namespace std;
//count number of times an item occurs in an array

int count(int A[], int n, int key) {
    if (n == 0) return 0;
    if (A[n-1] == key) return 1 + count(A,n-1,key);
    return 0 + count(A,n-1,key);
}

int count(string A, int n, char key) {
    if (n == 0) return 0;
    if (A[n-1] == key) return 1 + count(A,n-1,key);
    return 0 + count(A,n-1,key);
}

int main() {
    int n = 7;
    string S = "";
    cin >> S;
    
    int A[7] = {2,6,2,4,1,5,2}; //should output 3 if input is 2
    cout << "There are " << count(S,S.length(),'a') << " instances of 'a' in the string." << endl;
    cout << "There are " << count(A,n,2) << " instances of '2'  in the array" << endl;
}