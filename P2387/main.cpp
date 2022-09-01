#include <iostream>

using namespace std;

#define MAX_N 1001
#define MAX_M 2001

struct Edge {
    int to, next, d;

    Edge() {}

    Edge(int t, int n, int d) : to(t), next(n), d(d) {}
};

Edge edge[MAX_M * 2];
int n, m, head[MAX_N], edge_cnt;

void add_edge(int from, int to, int d) {
    edge[edge_cnt] = Edge(to, head[from], d);
    head[from] = edge_cnt++;
}

int dijkstra() {
    int dist[MAX_N];
    bool visit[MAX_N];

    memset(visit, false, sizeof visit);
    memset(dist, 0x3f, sizeof dist);
    visit[0] = true, dist[0] = 0;

    for (int i = head[0]; ~i; i = edge[i].next) dist[edge[i].to] = min(dist[edge[i].to], edge[i].d);

    for (int i = 0; i < n - 1; ++i) {
        int min = 0x3f3f3f3f, k = -1;
        for (int j = 1; j < n; ++j) {
            if (!visit[j] && dist[j] < min) {
                k = j;
                min = dist[j];
            }
        }
        visit[k] = true;
        for (int j = head[k]; ~j; j = edge[j].next) {
            int to = edge[j].to;
            if (!visit[to] && dist[k] + edge[j].d < dist[to]) {
                dist[to] = dist[k] + edge[j].d;
            }
        }
    }
    return dist[n - 1];
}

void init() {

    scanf("%d %d", &m, &n);

    memset(head, 0xff, sizeof head);
    edge_cnt = 0;

    int from, to, d;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &from, &to, &d);
        add_edge(from - 1, to - 1, d);
        add_edge(to - 1, from - 1, d);
    }

}

int main() {

    freopen("../a.in", "r", stdin);

    init();
    printf("%d", dijkstra());

    return 0;
}
