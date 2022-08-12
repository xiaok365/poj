#include <iostream>

using namespace std;

#define MAX_N 13
#define MAX_STATE 4096

int n, m, map[MAX_N];

bool ok(int row, int cur) {
    return !(cur & (cur << 1)) && (map[row] & cur) == cur;
}

void init() {
    int a[MAX_N][MAX_N];

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        int num = 0;
        for (int j = m - 1; j >= 0; --j) {
            num <<= 1;
            num += a[i][j];
        }
        map[i + 1] = num;
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    init();

    int state = 1 << m, dp[2][MAX_STATE] = {0};

    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < state; ++j) {
            dp[i & 1][j] = 0;
            if (ok(i, j)) {
                for (int last = 0; last < state; ++last) {
                    if (!(j & last)) {
                        dp[i & 1][j] += dp[(i - 1) & 1][last];
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < state; ++i) ans += dp[n & 1][i];

    cout << ans % 100000000;

    return 0;

}
