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
    edge_cnt = 0;
    name_cnt = 0;
    memset(head, 0xff, sizeof head);
    string boss, a, b;
    cin >> boss;
    name[name_cnt++] = boss;

    for (int i = 1; i < n; ++i) {
        cin >> a >> b;
        add_edge(find_id(b), find_id(a));
    }
}

void solve(int i) {
    dp[i][1] = 1;
    dp[i][0] = 0;
    same[i][0] = false;
    same[i][1] = false;
    int son_i = head[i];

    while (son_i != -1) {
        solve(edge[son_i].to);
        dp[i][1] += dp[edge[son_i].to][0];
        same[i][1] |= same[edge[son_i].to][0];

        dp[i][0] += max(dp[edge[son_i].to][0], dp[edge[son_i].to][1]);
        same[i][0] |= dp[edge[son_i].to][0] == dp[edge[son_i].to][1];

        son_i = edge[son_i].next;
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    while (cin >> n && n != 0) {
        init();
        solve(0);
        int ans = max(dp[0][0], dp[0][1]);


        bool unique = true;

        if (dp[0][0] == dp[0][1]) {
            unique = false;
        } else if (dp[0][0] > dp[0][1]) {
            if (same[0][0]) unique = false;
        } else {
            if (same[0][1]) unique = false;
        }

        if (unique) printf("%d Yes\n", ans); else printf("%d No\n", ans);
    }

    return 0;
}
