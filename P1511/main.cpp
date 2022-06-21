#include <iostream>
#include <fstream>

using namespace std;

#define INF 1000000000L

const int MAXN = 1000010;

struct Edge {
    long long to, value, next;

    Edge() {}

    Edge(long long t, long long v, long long n) : to(t), value(v), next(n) {}
};

long long n, m, head[MAXN], edgeCnt, a[MAXN][3], queue[MAXN];
long long d[MAXN];
Edge edge[MAXN];
bool visit[MAXN];

void init() {
    edgeCnt = 0;
    memset(head, 0xff, MAXN * 4);
    memset(visit, false, MAXN);
    for (int i = 2; i <= n; ++i) d[i] = INF;
}

void addEdge(long long from, long long to, long long value) {
    edge[edgeCnt] = Edge(to, value, head[from]);
    head[from] = edgeCnt++;
}

long long spfa() {

    long long top = 0, tail = 1;
    queue[0] = 1;
    visit[1] = true;
    d[1] = 0;

    while (top != tail) {
        long long u = queue[top];
        top = (top + 1) % (MAXN);
        visit[u] = false;
        long long headPoint = head[u];
        while (headPoint != -1) {
            Edge &temp = edge[headPoint];
            if (d[u] + temp.value < d[temp.to]) {
                d[temp.to] = d[u] + temp.value;
                if (!visit[temp.to]) {
                    queue[tail] = temp.to;
                    tail = (tail + 1) % (MAXN);
                    if (tail + 1 == top) {
                        cout << "queue full" << endl;
                        return 0;
                    }
                    visit[temp.to] = true;
                }
            }
            headPoint = temp.next;
        }
    }

    long long ans = 0;
    for (int i = 2; i <= n; ++i) {
        ans += d[i];
    }
    return ans;
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int t;
//    cin >> t;
    scanf("%d", &t);
    while (t--) {
//        cin >> n >> m;
        scanf("%d%d", &n, &m);
        init();
        for (int i = 0; i < m; ++i) {
            cin >> a[i][0] >> a[i][1] >> a[i][2];
            scanf("%d%d%d", a[i], a[i] + 1, a[i] + 2);
//            addEdge(a[i][0], a[i][1], a[i][2]);
        }
        long long ans = 0;
        ans += spfa();
        init();
        for (int i = 0; i < m; ++i) {
            addEdge(a[i][1], a[i][0], a[i][2]);
        }
        ans += spfa();
//        cout << ans << endl;
        printf("%ld\n", ans);
    }
    return 0;
}