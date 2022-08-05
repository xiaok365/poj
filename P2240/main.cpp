#include <iostream>
#include <string>
#include <map>

using namespace std;

#define MAX_N 31
#define MAX_M 1000

struct Edge {
    int from, to;
    double rate;

    Edge() {}

    Edge(int from, int to, double r) : from(from), to(to), rate(r) {}
};

Edge edge[MAX_M];

int n, edge_cnt;
double dist[MAX_N];

void add_edge(int from, int to, double r) {
    edge[edge_cnt++] = Edge(from, to, r);
}

void init() {
    edge_cnt = 0;
    memset(dist, 0xfe, sizeof dist);
    dist[0] = 1.0;
}

bool bellman() {

    for (int i = 1; i <= n; ++i) {

        bool update = false;
        for (int j = 0; j < edge_cnt; ++j) {
            Edge cur = edge[j];
            if (dist[cur.from] > 0 && dist[cur.from] * cur.rate > dist[cur.to]) {
                dist[cur.to] = dist[cur.from] * cur.rate;
                update = true;
            }
        }

        if (!update) {
            return false;
        }
    }

    // 总共n+1个结点，n次后还能更新，说明有环
    for (int j = 0; j < edge_cnt; ++j) {
        Edge cur = edge[j];
        if (dist[cur.from] > 0 && dist[cur.from] * cur.rate > dist[cur.to]) {
            return true;
        }
    }

    return false;
}

int main() {

    freopen("../a.in", "r", stdin);

    int index = 0, m;
    map<string, int> name;
    string st, from, to;
    double rate;

    while (scanf("%d", &n) && n != 0) {
        init();

        for (int i = 1; i <= n; ++i) {
            cin >> st;
            name[st] = i;
        }

        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            cin >> from >> rate >> to;
            add_edge(name[from], name[to], rate);
        }

        // 建立虚拟结点0，连向所有结点
        for (int i = 1; i <= n; ++i) {
            add_edge(0, i, 1.0);
        }

        if (bellman()) printf("Case %d: Yes\n", ++index); else printf("Case %d: No\n", ++index);
    }
    return 0;
}
