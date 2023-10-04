#include <iostream>

using namespace std;

#define MAX_N 5001

struct Stack {
    int data[MAX_N], top;

    Stack() : top(0) {}

    void Push(int x) { data[top++] = x; }

    int Pop() { return data[--top]; }

    int Size() { return top; }
};

struct Edge {
    int to, next;

    Edge() {}

    Edge(int t, int n) : to(t), next(n) {}
};

Edge edge1[MAX_N * MAX_N], edge2[MAX_N * MAX_N];

int edge_cnt1, edge_cnt2, head1[MAX_N], head2[MAX_N];
int node[MAX_N];// 缩点
bool visit[MAX_N];
Stack stack;

void add_edge(int from, int to) {
    edge1[edge_cnt1] = Edge(to, head1[from]);
    head1[from] = edge_cnt1++;
    edge2[edge_cnt2] = Edge(from, head2[to]);
    head2[to] = edge_cnt2++;
}

void init() {
    memset(head1, 0xff, sizeof head1);
    memset(head2, 0xff, sizeof head2);
    edge_cnt1 = edge_cnt2 = 0;
    int m, from, to;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &from, &to);
        add_edge(from, to);
    }
}

// 逆后序遍历反向图
void dfs2(int u) {
    visit[u] = true;
    for (int i = head2[u]; ~i; i = edge2[i].next) {
        int v = edge2[i].to;
        if (!visit[v]) dfs2(v);
    }
    stack.Push(u);
}

// 遍历正向图，缩点
void dfs1(int u, int represent) {
    visit[u] = true, node[u] = represent;
    for (int i = head1[u]; ~i; i = edge1[i].next) {
        int v = edge1[i].to;
        if (!visit[v]) dfs1(v, represent);
    }
}

void kosaraju(int n) {
    // 遍历反向图
    memset(visit, false, sizeof visit);
    for (int i = 1; i <= n; ++i) {
        if (!visit[i]) dfs2(i);
    }
    // 遍历正向图
    memset(visit, false, sizeof visit);
    while (stack.Size() > 0) {
        int u = stack.Pop();
        if (!visit[u]) dfs1(u, u);
    }
    // 缩点新图
    int out_degree[MAX_N] = {0};
    for (int i = 1; i <= n; ++i) {
        for (int j = head1[i]; ~j; j = edge1[j].next) {
            if (node[i] != node[edge1[j].to]) out_degree[node[i]]++;
        }
    }
    // 出度为0
    for (int i = 1; i <= n; ++i) {
        if (out_degree[node[i]] == 0) printf("%d ", i);
    }
    printf("\n");
}

int main() {
    freopen("../a.in", "r", stdin);
    int n;
    while (scanf("%d", &n) && n != 0) {
        init();
        kosaraju(n);
    }

    return 0;
}
