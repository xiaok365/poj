#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAXN = 201;

int a[MAXN] = {0};
int n = 0;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    string st;

    while (cin >> st && st != "0") {
        int m = st.size() - 1;
        n = max(n, m);
        for (int i = 0; i <= n; ++i) {
            if (m >= i) {
                a[i] += st[m - i] - '0';
                a[i + 1] += a[i] / 10;
                a[i] %= 10;
            } else {
                a[i + 1] += a[i] / 10;
                a[i] %= 10;
            }
        }
        if (a[n + 1] > 0) ++n;
    }

    while (a[n] == 0) --n;
    for (int i = n; i >= 0; --i) cout << a[i];

    return 0;
}