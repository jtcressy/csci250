#include <iostream>
#include <iomanip>

using namespace std;

int love() {
    char ans = '';
    cout << "Do you love me? (y/n)";
    cin >> ans;
    if (ans == 'y') {
        cout << "I love you too!" << endl;
        return 1;
    }
    return love();
}

int main() {
    return love();
}