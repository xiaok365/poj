#include <iostream>

using namespace std;

#define MAX_M 15001
int dp[2][MAX_M] = {0}, hook[20], weight[20];


int main() {
    freopen("../a.in", "r", stdin);

    memset(dp, 0, sizeof dp);
    dp[0][7500] = 1;

    int c, g;
    cin >> c >> g;
    for (int i = 0; i < c; ++i) cin >> hook[i];
    for (int i = 0; i < g; ++i) {
        cin >> weight[i];
    }

    // 枚举物品
    for (int i = 0; i < g; ++i) {
        // 枚举重量
        for (int j = 15000; j >= 0; --j) {
            // 当前初始化
            dp[(i + 1) & 1][j] = 0;
            // 枚举分组
            for (int k = 0; k < c; ++k) {
                int cur_w = hook[k] * weight[i];

                int last = j - cur_w;
                if (last >= 0 && last <= 15000) {
                    dp[(i + 1) & 1][j] += dp[i & 1][last];
                }
            }
        }
    }

    printf("%d", dp[g & 1][7500]);

    return 0;
}
