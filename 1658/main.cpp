#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, a[5];
    cin >> n;
    while (n--) {
        for (int i = 0; i < 4; ++i) {
            cin >> a[i];
        }
        bool equalDiff = false;
        if (a[1] * 2 == a[0] + a[2] && a[2] * 2 == a[1] + a[3]) equalDiff = true;
        if (equalDiff) {
            a[4] = a[3] * 2 - a[2];
        } else {
            a[4] = a[3] * a[3] / a[2];
        }
        for (int i = 0; i < 5; ++i) {
            cout << a[i] << " ";
        }
        cout << endl;
    }

    return 0;
}