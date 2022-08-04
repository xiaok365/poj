#include <iostream>

using namespace std;

#define MAX_N 501
int dist[MAX_N][MAX_N], n;

bool floyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
            if (dist[i][i] < 0) return true;
        }
    }

    return false;
}

int main() {

    freopen("../a.in", "r", stdin);

    int f, m, w, s, e, t;
    scanf("%d", &f);
    while (f--) {
        memset(dist, 0x3f, sizeof dist);
        for (int i = 1; i <= n; ++i) dist[i][i] = 0;

        scanf("%d %d %d", &n, &m, &w);

        for (int i = 0; i < m; ++i) {
            scanf("%d %d %d", &s, &e, &t);
            if (t < dist[s][e]) {
                dist[s][e] = dist[e][s] = t;
            }
        }

        for (int i = 0; i < w; ++i) {
            scanf("%d %d %d", &s, &e, &t);
            dist[s][e] = -t;
        }

        if (floyd()) printf("YES\n"); else printf("NO\n");
    }

    return 0;
}
