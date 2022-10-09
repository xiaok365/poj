#include <iostream>

using namespace std;

#define MAX_N 50010
#define INF 0x7fffffff

struct Edge {
    int to, value, next;

    Edge() {}

    Edge(int t, int v, int n) : to(t), value(v), next(n) {}
};

template<typename T>
struct Queue {
    static const int MAX_QUEUE_LEN = 50010;
    int head, tail;
    T data[MAX_QUEUE_LEN];

    Queue() : head(0), tail(0) { memset(data, 0, sizeof data); }

    bool is_not_empty() { return head != tail; }

    void push(T t) {
        data[tail] = t;
        tail = (tail + 1) % MAX_QUEUE_LEN;
    }

    T pop() {
        head = (head + 1) % MAX_QUEUE_LEN;
        return data[(head - 1 + MAX_QUEUE_LEN) % MAX_QUEUE_LEN];
    }
};

Edge edge[MAX_N * 3];
int head[MAX_N], edge_cnt = 0, source = INF, target = 0;

void add_edge(int from, int to, int value) {
    edge[edge_cnt] = Edge(to, value, head[from]);
    head[from] = edge_cnt++;
}

void init() {
    int n, a, b, c;
    memset(head, 0xff, sizeof head);

    scanf("%d", &n);
    while (n--) {
        scanf("%d %d %d", &a, &b, &c);
        if (b - a + 1 < c) c = b - a + 1;
        add_edge(b + 1, a, -c);
        source = min(source, a);
        target = max(target, b + 1);
    }
    for (int i = source; i < target; ++i) {
        add_edge(i + 1, i, 0);
        add_edge(i, i + 1, 1);
    }
}

int spfa() {
    int d[MAX_N];
    bool visit[MAX_N];

    memset(d, 0x3f, sizeof d);
    memset(visit, false, sizeof visit);

    Queue<int> queue;
    queue.push(target);
    visit[target] = true;
    d[target] = 0;

    while (queue.is_not_empty()) {
        int u = queue.pop();
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

    return -d[source];
}

int main() {
    freopen("../a.in", "r", stdin);
    init();
    printf("%d\n", spfa());
    return 0;
}