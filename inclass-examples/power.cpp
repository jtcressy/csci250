#include <iostream>

using namespaces std;

double power(double num, int n) {
    if (n==0) return 1.0;
    return num * power(num, n-1);
}

int main() {
    cout << power(3.14,3);
}