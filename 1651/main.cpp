#include <iostream>

using namespace std;

#define MAX_N 101
#define INF 0x3f3f3f3f

int n, a[MAX_N], dp[MAX_N][MAX_N];

int solve(int l, int r) {

    if (dp[l][r] != INF) return dp[l][r];
    if (l + 1 == r) return 0;

    dp[l][r] = INF;

    for (int i = l + 1; i < r; ++i) {
        dp[l][r] = min(dp[l][r], solve(l, i) + solve(i, r) + a[l] * a[r] * a[i]);
    }
    return dp[l][r];
}

int main() {

    freopen("../a.in", "r", stdin);

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    memset(dp, 0x3f, sizeof dp);
    printf("%d", solve(0, n - 1));

    return 0;
}
