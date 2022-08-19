#include <iostream>
#include <cmath>

using namespace std;
#define MAX_N 1002

int n, dp[MAX_N][2];
double height[MAX_N];

int main() {
    freopen("../a.in", "r", stdin);

    scanf("%d", &n);

    for (int i = 0; i < n; ++i) scanf("%lf", &height[i]);

    memset(dp, 0, sizeof dp);

    dp[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        dp[i][0] = 1;
        for (int j = 0; j < i; ++j) {
            if (height[i] > height[j]) {
                dp[i][0] = max(dp[i][0], dp[j][0] + 1);
            }
        }
    }

    dp[n - 1][1] = 1;
    for (int i = n - 2; i >= 0; --i) {
        dp[i][1] = 1;
        for (int j = n - 1; j > i; --j) {
            if (height[i] > height[j]) {
                dp[i][1] = max(dp[i][1], dp[j][1] + 1);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j)
            ans = max(ans, dp[i][0] + dp[j][1]);
    }

    printf("%d", n - ans);

    return 0;
}
