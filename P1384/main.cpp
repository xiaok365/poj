#include <iostream>
#include <cmath>

using namespace std;

#define MAX_N 501
#define MAX_M 10001

int n, m, value[MAX_N], weight[MAX_N], dp[MAX_M];

void init() {
    int a, b;
    scanf("%d %d %d", &a, &b, &n);
    m = b - a;
    for (int i = 0; i < n; ++i) scanf("%d %d", &value[i], &weight[i]);
    memset(dp, 0x3f, sizeof dp);
}

int main() {
    freopen("../a.in", "r", stdin);

    int t;
    scanf("%d", &t);
    while (t--) {

        init();
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = weight[i]; j <= m; ++j) {
                dp[j] = min(dp[j], dp[j - weight[i]] + value[i]);
            }
        }
        if (dp[m] == 0x3f3f3f3f) {
            printf("This is impossible.\n");
        } else {
            printf("The minimum amount of money in the piggy-bank is %d.\n", dp[m]);
        }
    }

    return 0;
}
