#include <iostream>
#include <cmath>

using namespace std;

#define MAX_N 10001
#define MAX_M 50001

struct Edge {
    int to, next;
    Edge() {}
    Edge(int t, int n) : to(t), next(n) {}
};

struct Stack {
    int data[MAX_N], top;
    Stack() : top(0) {}
    void Push(int x) { data[top++] = x; }
    int Pop() { return data[--top]; }
};

Edge edge[MAX_M];
int edge_cnt, head[MAX_N], n, m;
int dfn[MAX_N], low[MAX_N], order, vertex, node[MAX_N], cnt[MAX_N];
bool in_stack[MAX_N];
Stack stack;

void add_edge(int from, int to) {
    edge[edge_cnt] = Edge(to, head[from]);
    head[from] = edge_cnt++;
}

void init() {

    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(in_stack, false, sizeof in_stack);
    memset(cnt, 0, sizeof cnt);
    memset(node, 0, sizeof node);
    memset(head, 0xff, sizeof head);
    edge_cnt = order = vertex = 0;

    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        add_edge(from, to);
    }

}

void tarjan(int u) {
    dfn[u] = low[u] = ++order;
    stack.Push(u);
    in_stack[u] = true;

    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        vertex++;
        int k;
        do {
            k = stack.Pop();
            in_stack[k] = false;
            node[k] = vertex;
            cnt[vertex]++;
        } while (k != u);
    }

}

int main() {
    freopen("../a.in", "r", stdin);

    while (cin >> n >> m) {
        init();

        for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);

        int out[MAX_N] = {0}, ans = 0, k;
        for (int i = 1; i <= n; ++i) {
            for (int j = head[i]; j != -1; j = edge[j].next) {
                if (node[i] != node[edge[j].to]) out[node[i]]++;
            }
        }

        for (int i = 1; i <= vertex; ++i) {
            if (out[i] == 0) {
                ans++;
                k = i;
            }
        }
        if (ans == 1) printf("%d\n", cnt[k]); else { printf("0\n"); }
    }

    return 0;
}
