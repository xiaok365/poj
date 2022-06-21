#include <iostream>
#include <fstream>

using namespace std;

const int MAXM = 100001;

void init(bool f[]) {
    memset(f, false, MAXM);
    f[0] = true;
}

void dp(bool f[], int m, int cost) {
    for (int j = m; j >= cost; --j) {
        f[j] = f[j] | f[j - cost];
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    bool f[MAXM];
    int i, n, m, num, cost;
    while (cin >> m) {
        init(f);
        cin >> n;
        for (i = 0; i < n; ++i) {
            cin >> num >> cost;
            // 二进制分解物品
            int k = 1;
            while (k <= num) {
                dp(f, m, k * cost);
                num -= k;
                k <<= 1;
            }
            // 剩余物品
            if (num > 0) {
                dp(f, m, num * cost);
            }
        }
        for (i = m; i >= 0; --i) {
            if (f[i]) {
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}