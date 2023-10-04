#include <iostream>

using namespace std;

#define MAX_N 1001
#define MAX_M 31

int main() {

    freopen("../a.in", "r", stdin);

    int a[MAX_N], n, m, dp[MAX_M][MAX_N][2] = {0};

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

    for (int i = 0; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == 0) {
                dp[i][j][0] = dp[i][j - 1][0] + (a[j] & 1);
            } else {
                dp[i][j][0] = max(dp[i][j - 1][0], dp[i - 1][j - 1][1]) + (a[j] & 1);
                dp[i][j][1] = max(dp[i - 1][j - 1][0], dp[i][j - 1][1]) + ((a[j] >> 1) & 1);
            }
        }
    }

    printf("%d", max(dp[m][n][0], dp[m][n][1]));

    return 0;
}
