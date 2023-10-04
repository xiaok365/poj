#include <iostream>

#define MAX_N 501
int n, map[MAX_N][MAX_N], dist[MAX_N];

bool visit[MAX_N];

void init() {

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            scanf("%d", &map[i][j]);
        }
    }

    memset(visit, false, sizeof visit);
    for (int i = 0; i < n; ++i) {
        dist[i] = map[0][i];
    }
}

int prim() {

    int ans = 0;
    visit[0] = true;

    for (int i = 1; i < n; ++i) {

        int min = 0x7fffffff, k;
        for (int j = 1; j < n; ++j) {
            if (!visit[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }

        }

        if (min > ans) ans = min;

        // 将新的点k加入集合S,并通过k更新非S中点的距离
        visit[k] = true;
        for (int j = 1; j < n; ++j) {
            if (!visit[j] && map[k][j] < dist[j]) {
                dist[j] = map[k][j];
            }
        }
    }

    return ans;
}

int main() {

    freopen("../a.in", "r", stdin);

    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        printf("%d\n", prim());
    }

    return 0;
}
