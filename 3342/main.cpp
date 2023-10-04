#include <iostream>
#include <cmath>
#include <string>

using namespace std;

#define MAX_N 201

struct Edge {
    int to, next;

    Edge() {}

    Edge(int t, int n) : to(t), next(n) {}
};

Edge edge[MAX_N];
int n, edge_cnt, head[MAX_N], dp[MAX_N][2], same[MAX_N][2], name_cnt;
string name[MAX_N];

void add_edge(int from, int to) {
    edge[edge_cnt] = Edge(to, head[from]);
    head[from] = edge_cnt++;
}

int find_id(const string &employee) {
    for (int i = 0; i < name_cnt; ++i) {
        if (name[i] == employee) return i;
    }
    name[name_cnt++] = employee;
    return name_cnt - 1;
}

void init() {
    edge_cnt = name_cnt = 0;
    memset(head, 0xff, sizeof head);

    string boss, a, b;
    cin >> boss;
    name[name_cnt++] = boss;

    for (int i = 1; i < n; ++i) {
        cin >> a >> b;
        add_edge(find_id(b), find_id(a));
    }
}

void solve(int u) {
    dp[u][1] = 1, dp[u][0] = 0;
    same[u][0] = same[u][1] = false;

    for (int i = head[u]; i != -1; i = edge[i].next) {
        solve(edge[i].to);
        dp[u][1] += dp[edge[i].to][0];
        same[u][1] |= same[edge[i].to][0];

        dp[u][0] += max(dp[edge[i].to][0], dp[edge[i].to][1]);
        same[u][0] |= dp[edge[i].to][0] == dp[edge[i].to][1];
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    while (cin >> n && n != 0) {
        init();
        solve(0);

        bool unique = true;
        if (dp[0][0] == dp[0][1]) {
            unique = false;
        } else if (dp[0][0] > dp[0][1]) {
            if (same[0][0]) unique = false;
        } else {
            if (same[0][1]) unique = false;
        }

        int ans = max(dp[0][0], dp[0][1]);
        if (unique) printf("%d Yes\n", ans); else printf("%d No\n", ans);
    }

    return 0;
}
