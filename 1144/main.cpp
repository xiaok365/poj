#include <iostream>
#include <cmath>

using namespace std;

#define MAX_M 10001
#define MAX_N 101

struct Edge {
    int to, next;

    Edge() {}

    Edge(int t, int n) : to(t), next(n) {}
};

Edge edge[MAX_M];
int edge_cnt, head[MAX_N], dfn[MAX_N], low[MAX_N], order, son, ans;

void add_edge(int from, int to) {
    edge[edge_cnt] = Edge(to, head[from]);
    head[from] = edge_cnt++;
}

void init() {
    int from, to;
    memset(head, 0xff, sizeof head);
    memset(dfn, 0xff, sizeof dfn);
    edge_cnt = order = son = ans = 0;

    while (scanf("%d", &from) && from) {
        while (getchar() != '\n') {
            scanf("%d", &to);
            add_edge(from, to);
            add_edge(to, from);
        }
    }
}

void tarjan(int u) {
    dfn[u] = low[u] = order++;
    bool cut = false;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (dfn[v] == -1) {
            tarjan(v);
            low[u] = min(low[u], low[v]);

            if (u == 1) son++;
            else if (low[v] >= dfn[u]) cut = true;
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (cut) ans++;
}

int main() {

    freopen("../a.in", "r", stdin);

    int n;
    while (scanf("%d", &n) && n > 0) {
        init();
        tarjan(1);
        if (son > 1) ans++;
        printf("%d\n", ans);
    }
    return 0;
}
