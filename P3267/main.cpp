#include <iostream>

using namespace std;

#define MAX_N 601
#define MAX_M 301

int main() {
    freopen("../a.in", "r", stdin);

    int n, m, len[MAX_N] = {0}, dp[MAX_M];
    char msg[MAX_M], word[MAX_N][26];

    scanf("%d %d %s", &n, &m, msg);
    for (int i = 0; i < n; ++i) {
        scanf("%s", word[i]);
        len[i] = (int) strlen(word[i]);
    }

    dp[0] = 0;
    for (int i = 1; i <= m; ++i) {
        dp[i] = dp[i - 1] + 1;
        for (int j = 0; j < n; ++j) {
            // 从后向前匹配
            int a = i - 1, b = len[j] - 1;
            while (a >= 0 && b >= 0) {
                if (msg[a] == word[j][b]) {
                    a--, b--;
                } else a--;
            }
            // 匹配成功更新当前值
            if (b < 0) {
                dp[i] = min(dp[i], dp[a + 1] + i - 1 - a - len[j]);
            }
        }
    }

    printf("%d", dp[m]);

    return 0;
}
