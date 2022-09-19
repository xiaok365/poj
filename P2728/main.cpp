#include <iostream>
#include <cmath>

using namespace std;

#define MAX_N 1001

struct Node {
    int x, y, h;
};

Node node[MAX_N];

double d(Node &a, Node &b) {
    return sqrt(1.0 * (b.x - a.x) * (b.x - a.x) + 1.0 * (b.y - a.y) * (b.y - a.y));
}

double prim(int n, double lambda) {
    double map[MAX_N][MAX_N], dist[MAX_N], cost = 0, length = 0;
    int pre[MAX_N];
    bool visit[MAX_N] = {false};

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            map[i][j] = map[j][i] = abs(node[i].h - node[j].h) - lambda * d(node[i], node[j]);
        }
    }
    for (int i = 0; i < n; ++i) dist[i] = map[0][i], pre[i] = 0;
    visit[0] = true;
    for (int i = 1; i < n; ++i) {
        double min = 1e8;
        int k = -1;
        for (int j = 1; j < n; ++j) {
            if (!visit[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }
        cost += abs(node[pre[k]].h - node[k].h);
        length += d(node[pre[k]], node[k]);
        visit[k] = true;
        for (int j = 1; j < n; ++j) {
            if (!visit[j] && map[k][j] < dist[j]) {
                dist[j] = map[k][j];
                pre[j] = k;
            }
        }
    }
    return cost / length;
}

int main() {
    freopen("../a.in", "r", stdin);
    int n;
    while (~scanf("%d", &n) && n > 0) {
        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d", &node[i].x, &node[i].y, &node[i].h);
        }
        double ans, last = 0;
        while (true) {
            ans = prim(n, last);
            if (fabs(ans - last) < 1e-6) break;
            last = ans;
        }
        printf("%.3lf\n", ans);
    }
    return 0;
}
