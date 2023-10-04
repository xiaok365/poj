#include <iostream>
#include <fstream>

using namespace std;

int countOne(int n) {
    int total = 0;
    while (n > 0) {
        total++;
        n &= n - 1;
    }
    return total;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int i, n, k, line[8], f[2][256], num[256];
    char ch;

    for (i = 0; i < 256; ++i) num[i] = countOne(i);

    while (cin >> n >> k && n > 0) {

        for (i = 0; i < n; ++i) {
            int t = 0;
            for (int j = 0; j < n; ++j) {
                t <<= 1;
                cin >> ch;
                if (ch == '.') t += 1;
            }
            line[i] = t;
        }

        memset(f, 0, 2 * 256 * 4);
        f[0][0] = 1;
        int j, c, now = 0;

        for (i = 0; i < n; ++i) {
            now = 1 - now;

            for (j = 0; j < 256; ++j)
                if (num[j] <= k) {
                    //第i行不放棋子
                    f[now][j] += f[1 - now][j];

                    //第i行放棋子
                    for (c = 0; c < n; ++c) {
                        if ((j & 1 << c) == 0 && (line[i] & 1 << c) == 0) {
                            f[now][j | 1 << c] += f[1 - now][j];
                        }
                    }
                }
        }

        int ans = 0;
        for (i = 0; i < 256; ++i) {
            if (num[i] == k) {
                ans += f[now][i];
            }
        }
        cout << ans << endl;
    }
    return 0;
}