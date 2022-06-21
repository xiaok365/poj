#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 50010, INF = 0x7fffffff;

struct Edge {
    int to, value, next;

    Edge() {}

    Edge(int t, int v, int n) : to(t), value(v), next(n) {}
};

Edge edge[MAXN * 3];
int n, head[MAXN], edgeCnt = 0, queue[MAXN], d[MAXN];
bool visit[MAXN];

void addEdge(int from, int to, int value) {
    edge[edgeCnt] = Edge(to, value, head[from]);
    head[from] = edgeCnt++;
}

void init() {
    memset(head, 0xff, MAXN * 4);
}

int spfa(int source, int target) {

    int top = 0, tail = 1;
    for (int i = source; i <= target; ++i) {
        visit[i] = false;
        d[i] = INF;
    }
    queue[0] = target;
    visit[target] = true;
    d[target] = 0;

    while (top != tail) {
        int u = queue[top];
        top = (top + 1) % (MAXN);
        visit[u] = false;
        int headPoint = head[u];
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
    return -d[source];
}

int main() {

    ifstream cin("../a.in");
    ofstream cout("../a.out");

    int a, b, c, source = INF, target = 0;
    init();
    cin >> n;
    while (n--) {
        cin >> a >> b >> c;
        if (b - a + 1 < c) c = b - a + 1;
        addEdge(b + 1, a, -c);
        source = min(source, a);
        target = max(target, b + 1);
    }
    for (int i = source; i < target; ++i) {
        addEdge(i + 1, i, 0);
        addEdge(i, i + 1, 1);
    }
    cout << spfa(source, target) << endl;
    return 0;
}