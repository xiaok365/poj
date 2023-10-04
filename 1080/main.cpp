#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 101;

int value[5][5] = {{5,  -1, -2, -1, -3},
                   {-1, 5,  -3, -2, -4},
                   {-2, -3, 5,  -2, -2},
                   {-1, -2, -2, 5,  -1},
                   {-3, -4, -2, -1, -100}};

int get(char ch) {
    switch (ch) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
        default:
            return 4;
    }
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t, n, m, i, j, f[MAXN][MAXN] = {0};
    char a[MAXN], b[MAXN];
    cin >> t;
    while (t--) {
        cin >> n;
        for (i = 1; i <= n; ++i) cin >> a[i];
        cin >> m;
        for (i = 1; i <= m; ++i) cin >> b[i];

        // 初始化最小值
        for (i = 0; i < MAXN; ++i)
            for (j = 0; j < MAXN; ++j) f[i][j] = 0x80000000;

        f[0][0] = 0;
        for (i = 1; i <= n; ++i) {
            f[i][0] = f[i - 1][0] + value[4][get(a[i])];
        }
        for (i = 1; i <= m; ++i) {
            f[0][i] = f[0][i - 1] + value[4][get(b[i])];
        }

        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= m; ++j) {
                f[i][j] = max(f[i - 1][j] + value[4][get(a[i])], f[i][j - 1] + value[4][get(b[j])]);
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + value[get(a[i])][get(b[j])]);
            }
        }
        cout << f[n][m] << endl;
    }
    return 0;
}