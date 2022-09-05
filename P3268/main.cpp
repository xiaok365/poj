#include <iostream>

using namespace std;

#define MAX_N 1001

int n, map[MAX_N][MAX_N];

void dijkstra(int start, int dist[]) {

    bool visit[MAX_N];
    memset(visit, false, sizeof visit);
    visit[start] = true;

    for (int i = 0; i < n; ++i) dist[i] = map[start][i];

    for (int i = 0; i < n - 1; ++i) {
        int min = 0x7fffffff, k = -1;
        for (int j = 0; j < n; ++j) {
            if (!visit[j] && dist[j] < min) {
                k = j;
                min = dist[j];
            }
        }
        visit[k] = true;
        for (int j = 0; j < n; ++j) {
            if (!visit[j]) {
                if (dist[k] + map[k][j] < dist[j]) dist[j] = dist[k] + map[k][j];
            }
        }
    }
}

void transpose() {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int t = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = t;
        }
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    int m, x, from, to, d;

    scanf("%d %d %d", &n, &m, &x);
    x--;

    memset(map, 0x3f, sizeof map);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &from, &to, &d);
        map[from - 1][to - 1] = d;
    }

    for (int i = 0; i < n; ++i) map[i][i] = 0;

    int dist1[MAX_N], dist2[MAX_N], ans = 0;
    dijkstra(x, dist1);
    transpose();
    dijkstra(x, dist2);

    for (int i = 0; i < n; ++i) {
        ans = max(ans, dist1[i] + dist2[i]);
    }

    printf("%d", ans);

    return 0;
}
