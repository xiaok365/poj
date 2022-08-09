#include <iostream>
#include <cmath>

using namespace std;

#define MAX_N 6001

struct Edge {
    int to, next;
    Edge();
    Edge(int t, int n) : to(t), next(n) {}
};

Edge edge[MAX_N];
int n, value[MAX_N], edge_cnt = 0, head[MAX_N], dp[MAX_N][2], in_degree[MAX_N] = {0};

void add_edge(int from, int to) {
    edge[edge_cnt] = Edge(to, head[from]);
    head[from] = edge_cnt++;
    in_degree[to]++;
}

void init() {
    // 读入value
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> value[i];

    // 读入边
    memset(head, 0xff, sizeof head);
    int l, k;
    while (cin >> l >> k && !(l == 0 && k == 0)) {
        add_edge(k, l);
    }
}

int find_root() {
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) return i;
    }
    return 0;
}

void solve(int i) {
    dp[i][1] = value[i];
    dp[i][0] = 0;
    int son_i = head[i];
    while (son_i != -1) {
        solve(edge[son_i].to);
        dp[i][1] += dp[edge[son_i].to][0];
        dp[i][0] += max(dp[edge[son_i].to][0], dp[edge[son_i].to][1]);
        son_i = edge[son_i].next;
    }
}

int main() {
    freopen("../a.in", "r", stdin);
    init();
    int root = find_root();
    solve(root);
    printf("%d", max(dp[root][0], dp[root][1]));
    return 0;
}
