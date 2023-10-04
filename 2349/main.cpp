#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAX_N 501

int s, n;
double map[MAX_N][MAX_N];

double d(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void init() {
    scanf("%d %d", &s, &n);
    int x[MAX_N], y[MAX_N];

    for (int i = 0; i < n; ++i) scanf("%d %d", &x[i], &y[i]);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            map[i][j] = map[j][i] = d(x[i], y[i], x[j], y[j]);
        }
    }
}

double prim() {

    double ans[MAX_N], dist[MAX_N];
    bool visit[MAX_N] = {false};

    visit[0] = true;
    fill(dist, dist + n, 0x3f3f3f3f);

    for (int i = 0; i < n; ++i) dist[i] = map[0][i];

    for (int i = 1; i < n; ++i) {
        double min = 0x3f3f3f3f;
        int k = -1;
        for (int j = 1; j < n; ++j) {
            if (!visit[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }
        ans[i] = min;
        visit[k] = true;
        for (int j = 1; j < n; ++j) {
            if (!visit[j] && map[k][j] < dist[j]) {
                dist[j] = map[k][j];
            }
        }
    }
    sort(dist + 1, dist + n);
    return dist[n - s];
}

int main() {
    freopen("../a.in", "r", stdin);

    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        printf("%.2lf\n", prim());
    }
    return 0;
}
