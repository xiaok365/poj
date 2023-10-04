#include <iostream>

using namespace std;

#define INF 10000000000L
#define MAX_N 1000010
#define LL long long

struct Edge {
    int to, value, next;

    Edge() {}

    Edge(int t, int v, int n) : to(t), value(v), next(n) {}
};

template<typename T>
struct Queue {
    int head, tail;
    T data[MAX_N];

    Queue() : head(0), tail(0) { memset(data, 0, sizeof data); }

    bool is_not_empty() { return head != tail; }

    void push(T t) {
        data[tail] = t;
        tail = (tail + 1) % MAX_N;
    }

    T pop() {
        head = (head + 1) % MAX_N;
        return data[(head - 1 + MAX_N) % MAX_N];
    }
};

int n, m, head[MAX_N], edgeCnt, a[MAX_N][3];
LL d[MAX_N];
Edge edge[MAX_N];
bool visit[MAX_N];

void init() {
    edgeCnt = 0;
    memset(head, 0xff, sizeof head);
    memset(visit, false, sizeof visit);
    for (int i = 2; i <= n; ++i) d[i] = INF;
}

void add_edge(int from, int to, int value) {
    edge[edgeCnt] = Edge(to, value, head[from]);
    head[from] = edgeCnt++;
}

LL spfa() {
    Queue<int> queue;
    queue.push(1);
    visit[1] = true;
    d[1] = 0;
    while (queue.is_not_empty()) {
        LL u = queue.pop();
        visit[u] = false;
        for (int i = head[u]; ~i; i = edge[i].next) {
            Edge &t = edge[i];
            if (d[u] + t.value < d[t.to]) {
                d[t.to] = d[u] + t.value;
                if (!visit[t.to]) {
                    queue.push(t.to);
                    visit[t.to] = true;
                }
            }
        }
    }

    LL ret = 0;
    for (int i = 2; i <= n; ++i) ret += d[i];
    return ret;
}

int main() {
    freopen("../a.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        init();
        for (int i = 0; i < m; ++i) {
            scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
            add_edge(a[i][0], a[i][1], a[i][2]);
        }
        LL ans = spfa();
        init();
        for (int i = 0; i < m; ++i) add_edge(a[i][1], a[i][0], a[i][2]);
        printf("%lld\n", ans + spfa());
    }
    return 0;
}