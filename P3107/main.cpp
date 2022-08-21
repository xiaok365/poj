#include <iostream>
#include <cmath>

#define  MAX_N 50001
#define  MAX_M 100001

using namespace std;

struct Edge {
    int to, next;

    Edge() {}

    Edge(int t, int n) : to(t), next(n) {}
};

Edge edge[MAX_M];
int edge_cnt, head[MAX_N], n, cnt[MAX_N], ans;

void add_edge(int from, int to) {
    edge[edge_cnt] = Edge(to, head[from]);
    head[from] = edge_cnt++;
}

int dfs(int u, int father) {
    int size = 1;
    for (int i = head[u]; ~i; i = edge[i].next) {
        if (father == edge[i].to) continue;
        int j = dfs(edge[i].to, u);
        size += j;
        cnt[u] = max(cnt[u], j);
    }
    cnt[u] = max(cnt[u], n - size);
    return size;
}

void init() {
    ans = 0x7fffffff;
    edge_cnt = 0;
    memset(cnt, 0, sizeof cnt);
    memset(head, 0xff, sizeof head);

    scanf("%d", &n);
    int from, to;
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d %d", &from, &to);
        add_edge(from, to);
        add_edge(to, from);
    }

}

int main() {

    freopen("../a.in", "r", stdin);

    init();
    dfs(1, 0);

    for (int i = 1; i <= n; ++i) {
        ans = min(ans, cnt[i]);
    }
    for (int i = 1; i <= n; ++i) {
        if (cnt[i] == ans) printf("%d ", i);
    }

    return 0;
}
