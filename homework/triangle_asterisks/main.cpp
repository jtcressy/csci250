//
// Created by Joel Cressy on 9/9/2017.
//

#include <iostream>
#include <iomanip>

using namespace std;

void asterisks(int n) {
    if (n == 0) return;
    cout << "*";
    asterisks(n-1);
}

void triangles(int n) {
    if (n == 0) return;
    asterisks(n);
    cout << endl;
    triangles(n-1);
    asterisks(n);
    cout << endl;
}

int main() {
    int size;
    cout << "Enter size of triangle: ";
    cin >> size;
    cout << endl;
    triangles(size);
    return 0;
}