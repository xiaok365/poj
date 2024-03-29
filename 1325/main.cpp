#include <iostream>

#define MAX_N 101
int n, m, right[MAX_N];
bool map[MAX_N][MAX_N], visit[MAX_N];

bool hungary(int u) {
    for (int i = 0; i < m; ++i) {
        if (!visit[i] && map[u][i]) {
            visit[i] = true;
            if (right[i] == -1 || hungary(right[i])) {
                right[i] = u;
                return true;
            }
        }
    }
    return false;
}

void init() {
    memset(map, false, sizeof map);
    memset(right, 0xff, sizeof right);

    int task;
    scanf("%d %d", &m, &task);
    int index, x, y;
    for (int i = 0; i < task; ++i) {
        scanf("%d %d %d", &index, &x, &y);
        if (x != 0 && y != 0) map[x][y] = true;
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    while (scanf("%d", &n) && n > 0) {
        init();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            memset(visit, false, sizeof visit);
            ans += hungary(i);
        }
        printf("%d\n", ans);
    }

    return 0;
}
