#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

#define MAX_N 101
int n, map[MAX_N][MAX_N], dist[MAX_N];
bool visit[MAX_N];

int digit(const char st[], int len) {

    int ret = 0;
    for (int i = 0; i < len; ++i) {
        ret = ret * 10 + st[i] - '0';
    }
    return ret;
}


int dijkstra() {

    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        int min = 0x7fffffff, k = -1;

        for (int j = 1; j < n; ++j) {
            if (!visit[j] && dist[j] < min) {
                k = j;
                min = dist[j];
            }
        }
        ans = max(ans, min);
        visit[k] = true;
        for (int j = 1; j < n; ++j) {
            if (!visit[j]) {
                if (dist[k] + map[k][j] < dist[j]) dist[j] = dist[k] + map[k][j];
            }
        }
    }

    return ans;
}

void init() {

    memset(map, 0, sizeof map);

    char st[10];

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            scanf("%s", st);
            if (st[0] == 'x') {
                map[i][j] = map[j][i] = 0x3f3f3f3f;
            } else {
                map[i][j] = map[j][i] = digit(st, (int) strlen(st));
            }
        }
    }

    memset(visit, false, sizeof visit);
    visit[0] = true;

    dist[0] = 0;
    for (int i = 1; i < n; ++i) {
        dist[i] = map[0][i];
    }

}

int main() {

    freopen("../a.in", "r", stdin);

    scanf("%d", &n);

    init();

    printf("%d", dijkstra());

    return 0;
}
