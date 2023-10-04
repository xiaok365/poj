#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int f[10001];

int calc(int n) {
    if (n == 1)
        return 1;

    if (n < 10001 && f[n] != -1)
        return f[n];

    int x = 0;
    if (n & 1) {
        x = calc(3 * n + 1) + 1;
    } else {
        x = calc(n / 2) + 1;
    }
    if (n < 10001) f[n] = x;
    return x;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int a, b;
    memset(f, 0xff, 10000 * 4);
    while (cin >> a >> b) {
        int a1 = a, b1 = b, ans = 0;
        if (a1 > b1) {
            a1 ^= b1 ^= a1 ^= b1;
        }
        for (int i = a1; i <= b1; ++i) {
            ans = max(ans, calc(i));
        }
        cout << a << " " << b << " " << ans << endl;
    }
    return 0;
}