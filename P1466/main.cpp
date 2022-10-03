#include <iostream>

#define MAX_N 501

struct Edge {
    int to, next;

    Edge() {}

    Edge(int t, int n) : to(t), next(n) {}
};

Edge edge[MAX_N * MAX_N];
int edge_cnt, head[MAX_N], match[MAX_N];
bool visit[MAX_N];

void add_edge(int from, int to) {
    edge[edge_cnt] = Edge(to, head[from]);
    head[from] = edge_cnt++;
}

void init(int n) {
    memset(match, 0xff, sizeof match);
    memset(head, 0xff, sizeof head);
    edge_cnt = 0;
    int from, to, m;
    for (int i = 0; i < n; ++i) {
        scanf("%d: (%d)", &from, &m);
        for (int j = 0; j < m; ++j) {
            scanf("%d", &to);
            add_edge(from, to);
        }
    }
}

bool hungary(int u) {
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (!visit[v]) {
            visit[v] = true;
            if (match[v] == -1 || hungary(match[v])) {
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    freopen("../a.in", "r", stdin);
    int n;
    while (~scanf("%d", &n)) {
        init(n);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (match[i] == -1) {
                memset(visit, false, sizeof visit);
                if (hungary(i)) {
                    ans++;
                }
            }
        }
        printf("%d\n", n - ans);
    }
    return 0;
}
