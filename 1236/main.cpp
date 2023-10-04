#include <iostream>
#include <cmath>

using namespace std;

#define MAX_N 101
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
int edge_cnt, head[MAX_N], n;
int dfn[MAX_N], low[MAX_N], order, vertex, node[MAX_N];
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
    memset(node, 0, sizeof node);
    memset(head, 0xff, sizeof head);
    edge_cnt = order = vertex = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int to;
        while (scanf("%d", &to) && to > 0) {
            add_edge(i + 1, to);
        }
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
        } while (k != u);
    }

}

int main() {
    freopen("../a.in", "r", stdin);

    init();

    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);

    int in[MAX_N] = {0}, out[MAX_N] = {0};
    for (int i = 1; i <= n; ++i) {
        for (int j = head[i]; j != -1; j = edge[j].next) {
            if (node[i] != node[edge[j].to]) {
                in[node[edge[j].to]]++;
                out[node[i]]++;
            }
        }
    }

    int in_cnt = 0, out_cnt = 0;
    for (int i = 1; i <= vertex; ++i) {
        if (in[i] == 0) in_cnt++;
        if (out[i] == 0) out_cnt++;
    }
    if (vertex == 1) printf("1\n0\n"); else printf("%d\n%d\n", in_cnt, max(in_cnt, out_cnt));

    return 0;
}
