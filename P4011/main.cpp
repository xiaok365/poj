#include <iostream>

using namespace std;

int main() {

    int n;
    cin >> n;
    if (n > 199) {
        cout << 0 << endl;
    } else {
        cout << 199 - n << endl;
    }

    return 0;
}