#include <iostream>

using namespace std;

int main() {

    int a, b;
    while (cin >> a >> b) {
        if (b == 0) continue;
        int s = a / b;
        cout << a - s * b << endl;
    }
    return 0;
}