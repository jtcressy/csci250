#include <iostream>
#include <string>
using namespace std;

string asterisks(int n) {
    if (n==0) return "";
    return "*" + asterisks(n-1);
}

int main() {
    int num;
    cin >> num;
    cout << asterisks(num) << endl;
}
