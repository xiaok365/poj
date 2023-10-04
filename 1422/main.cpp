#include <iostream>

#define MAX_N 121

int n, match[MAX_N];
bool map[MAX_N][MAX_N], visit[MAX_N];

bool hungary(int u) {
    for (int i = 1; i <= n; ++i) {
        if (!visit[i] && map[u][i]) {
            visit[i] = true;
            if (match[i] == -1 || hungary(match[i])) {
                match[i] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {

    freopen("../a.in", "r", stdin);
    int t, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);

        memset(map, false, sizeof map);
        memset(match, 0xff, sizeof match);

        for (int i = 0; i < m; ++i) {
            int from, to;
            scanf("%d %d", &from, &to);
            map[from][to] = true;
        }

        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            memset(visit, false, sizeof visit);
            cnt += hungary(i);
        }
        printf("%d\n", n - cnt);
    }

    return 0;
}
