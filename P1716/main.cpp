#include <iostream>

using namespace std;

#define MAX_N 10010
#define INF 0x7fffffff

struct Edge {
    int to, value, next;

    Edge() {}

    Edge(int t, int v, int n) : to(t), value(v), next(n) {}
};

template<typename T>
struct Queue {
    static const int MAX_QUEUE_LEN = 10010;
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
int n, head[MAX_N], edgeCnt = 0, source = INF, target = 0;

void add_edge(int from, int to, int value) {
    edge[edgeCnt] = Edge(to, value, head[from]);
    head[from] = edgeCnt++;
}

void init() {
    memset(head, 0xff, sizeof head);

    int a, b;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &a, &b);
        add_edge(a, b + 1, 2);
        source = min(source, a);
        target = max(target, b + 1);
    }
    for (int i = source; i < target; ++i) {
        add_edge(i, i + 1, 0);
        add_edge(i + 1, i, -1);
    }

}

int spfa() {

    int dist[MAX_N];
    bool visit[MAX_N];

    memset(dist, 0xcf, sizeof dist);
    memset(visit, false, sizeof visit);

    Queue<int> queue;
    queue.push(source);
    dist[source] = 0;
    visit[source] = true;

    while (queue.is_not_empty()) {
        int u = queue.pop();
        visit[u] = false;
        for (int i = head[u]; ~i; i = edge[i].next) {
            Edge &t = edge[i];
            if (dist[u] + t.value > dist[t.to]) {
                dist[t.to] = dist[u] + t.value;
                if (!visit[t.to]) {
                    queue.push(t.to);
                    visit[t.to] = true;
                }
            }
        }
    }
    return dist[target];
}

int main() {
    freopen("../a.in", "r", stdin);
    init();
    printf("%d", spfa());
    return 0;
}