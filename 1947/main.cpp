#include <iostream>
#include <cmath>

using namespace std;

#define MAX_N 151

struct Edge {
    int to, next;
    Edge() : to(0), next(-1) {}
    Edge(int t, int n) : to(t), next(n) {}
};

Edge edge[MAX_N];

int head[MAX_N], son_size[MAX_N], edge_cnt, n, p, father[MAX_N], dp[MAX_N][MAX_N];

void add_edge(int from, int to) {
    edge[edge_cnt] = Edge(to, head[from]);
    son_size[from]++;
    head[from] = edge_cnt++;
}

int find_root() {
    int i = 1;
    while (father[i] != -1) i = father[i];
    return i;
}

void init() {

    memset(head, 0xff, sizeof head);
    memset(father, 0xff, sizeof father);
    memset(son_size, 0, sizeof son_size);
    memset(dp, 0x3f, sizeof dp);
    edge_cnt = 0;

    cin >> n >> p;

    int from, to;

    for (int i = 1; i < n; ++i) {
        cin >> from >> to;
        add_edge(from, to);
        father[to] = from;
    }
}

void solve(int root) {

    if (father[root] == -1) dp[root][1] = son_size[root];
    else dp[root][1] = son_size[root] + 1;

    // 枚举物品
    for (int i = head[root]; i != -1; i = edge[i].next) {
        int son = edge[i].to;
        solve(son);
        // 枚举重量
        for (int j = p; j >= 2; --j) {
            // 枚举分组
            for (int k = 1; k < j; ++k) {
                dp[root][j] = min(dp[root][j], dp[root][j - k] + dp[son][k] - 2);
            }
        }
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    init();
    solve(find_root());

    int ans = 0x7fffffff;
    for (int i = 1; i <= n; ++i) {
        ans = min(ans, dp[i][p]);
    }

    cout << ans;

    return 0;
}
