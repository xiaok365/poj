#include <iostream>
#include <fstream>

using namespace std;

void init(int a[]) {
    int i, i2, i3, i5;
    i2 = i3 = i5 = 0;
    a[0] = 1;
    for (i = 1; i < 1500; ++i) {
        int temp = min(a[i2] * 2, min(a[i3] * 3, a[i5] * 5));
        a[i] = temp;
        if (temp == a[i2] * 2) {
            i2++;
        }
        if (temp == a[i3] * 3) {
            i3++;
        }
        if (temp == a[i5] * 5) {
            i5++;
        }
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int n, a[1500];
    init(a);
    while (cin >> n && n > 0) {
        cout << a[n - 1] << endl;
    }
    return 0;
}