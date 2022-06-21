#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 1025;

int f[MAXN][MAXN] = {0}, n;

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int y, int value) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= n; j += lowbit(j)) {
            f[i][j] += value;
        }
    }
}

int sum(int x, int y) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            ans += f[i][j];
        }
    }
    return ans;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");
    int instruction;
    while (cin >> instruction && instruction != 3) {
        switch (instruction) {
            case 0:
                cin >> n;
                break;
            case 1:
                int i, j, value;
                cin >> i >> j >> value;
                add(i + 1, j + 1, value);
                break;
            case 2:
                int l, b, r, t;
                cin >> l >> b >> r >> t;
                cout << sum(r + 1, t + 1) + sum(l, b) - sum(r + 1, b) - sum(l, t + 1) << endl;
                break;
            default:;
        }
    }
    return 0;
}