#include <iostream>
#include <cmath>

#define  MAX_N 20001
#define  MAX_M 40001

using namespace std;

struct Edge {
    int to, next;

    Edge() {}

    Edge(int t, int n) : to(t), next(n) {}
};


Edge edge[MAX_M];
int edge_cnt, head[MAX_N], n, ans, node;

void add_edge(int from, int to) {
    edge[edge_cnt] = Edge(to, head[from]);
    head[from] = edge_cnt++;
}

int dfs(int u, int father) {
    int size = 1, cur_max = 0;
    for (int i = head[u]; ~i; i = edge[i].next) {
        if (father == edge[i].to) continue;
        int j = dfs(edge[i].to, u);
        size += j;
        cur_max = max(cur_max, j);
    }
    cur_max = max(cur_max, n - size);
    if (cur_max < ans) {
        ans = cur_max;
        node = u;
    }
    return size;
}

void init() {
    ans = 0x7fffffff;
    edge_cnt = node = 0;
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

    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        dfs(1, 0);
        printf("%d %d\n", node, ans);
    }

    return 0;
}
