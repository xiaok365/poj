#include <iostream>
#include <vector>

#define MAX_N 201
#define MAX_M 21
#define MAX_STATE 801
#define FIX 400

int main() {

    freopen("../a.in", "r", stdin);

    int n, m, p[MAX_N], d[MAX_N], cases = 0;

    while (scanf("%d %d", &n, &m) && !(n == 0 && m == 0)) {
        for (int i = 0; i < n; ++i) scanf("%d %d", &p[i], &d[i]);

        int dp[MAX_M][MAX_STATE];
        std::vector<int> path[MAX_M][MAX_STATE];

        memset(dp, 0xff, sizeof dp);
        dp[0][0 + FIX] = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = m; j > 0; --j) {
                for (int k = -400; k <= 400; ++k) {
                    int s = p[i] - d[i], t = p[i] + d[i];

                    if (k - s < -400 || k - s > 400) continue;
                    if (dp[j - 1][k - s + FIX] == -1) continue;

                    if (dp[j - 1][k - s + FIX] + t > dp[j][k + FIX]) {
                        dp[j][k + FIX] = dp[j - 1][k - s + FIX] + t;
                        path[j][k + FIX] = path[j - 1][k - s + FIX];
                        path[j][k + FIX].push_back(i);
                    }
                }
            }
        }

        int k = -400;
        for (int i = -400; i <= 400; ++i) {
            if (dp[m][i + FIX] == -1) continue;
            if (abs(i) < abs(k) || abs(i) == abs(k) && dp[m][i + FIX] > dp[m][k + FIX]) k = i;
        }

        int prosecution = 0, defence = 0;
        for (int i = 0; i < m; ++i) {
            prosecution += p[path[m][k + FIX][i]];
            defence += d[path[m][k + FIX][i]];
        }

        printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence: \n", ++cases, prosecution,
               defence);

        for (int i = 0; i < m; ++i) {
            printf(" %d", path[m][k + FIX][i] + 1);
        }

    }

    return 0;
}
