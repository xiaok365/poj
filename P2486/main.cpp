#include <iostream>
#include <cmath>

using namespace std;

#define MAX_N 101
#define MAX_M 201

struct Edge {
    int to, next;
    Edge() {}
    Edge(int t, int n) : to(t), next(n) {}
};

Edge edge[MAX_N];
int n, m, value[MAX_N], head[MAX_N], edge_cnt, dp[MAX_N][MAX_M][2];

void add_edge(int from, int to) {
    edge[edge_cnt] = Edge(to, head[from]);
    head[from] = edge_cnt++;
}

void init() {
    memset(head, 0xff, sizeof head);
    memset(dp, 0, sizeof dp);
    edge_cnt = 0;

    // 点值
    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
    }

    // 边
    for (int i = 1; i < n; ++i) {
        int from, to;
        cin >> from >> to;
        if (from > to) from ^= to ^= from ^= to;
        add_edge(from, to);
    }
}

// dp[i][j][0]:回到当前点, dp[i][j][1]:不回到当前点
void solve(int u) {

    dp[u][0][0] = dp[u][0][1] = value[u];

    // 枚举物品
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        solve(v);
        // 枚举重量
        for (int j = m; j >= 1; --j) {
            // 分组
            for (int k = 0; k < j; ++k) {
                if (k <= j - 2) {
                    dp[u][j][0] = max(dp[u][j][0], dp[u][j - k - 2][0] + dp[v][k][0]);
                    dp[u][j][1] = max(dp[u][j][1], dp[u][j - k - 2][1] + dp[v][k][0]);
                }
                dp[u][j][1] = max(dp[u][j][1], dp[u][j - k - 1][0] + dp[v][k][1]);
            }
        }
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    while (cin >> n >> m) {
        init();
        solve(1);
        int ans = 0;
        for (int i = 0; i <= m; ++i) {
            ans = max(ans, max(dp[1][i][1], dp[1][i][0]));
        }
        printf("%d\n", ans);
    }

    return 0;
}
