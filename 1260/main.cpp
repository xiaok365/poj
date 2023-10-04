#include <iostream>
#include <cmath>

using namespace std;
#define MAX_N 101
int n, sum[MAX_N], dp[MAX_N], price[MAX_N];

void init() {
    memset(sum, 0, sizeof sum);
    memset(dp, 0x3f, sizeof dp);

    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &sum[i], &price[i]);
        sum[i] += sum[i - 1];
    }
}

int main() {

    freopen("../a.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] = min(dp[i], dp[j] + (sum[i] - sum[j] + 10) * price[i]);
            }
        }

        printf("%d\n", dp[n]);
    }

    return 0;
}
