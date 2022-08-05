#include <iostream>

using namespace std;

#define MAX_N 2001

int n, dist[MAX_N], map[MAX_N][MAX_N];
char types[MAX_N][8];
bool visit[MAX_N];


int calc(const char a[], const char b[]) {
    int cnt = 0;
    for (int i = 0; i < 7; ++i) {
        if (a[i] != b[i]) cnt++;
    }
    return cnt;
}

void init() {

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            map[i][j] = map[j][i] = calc(types[i], types[j]);
        }
    }
    for (int i = 1; i < n; ++i) {
        dist[i] = map[0][i];
    }
    dist[0] = 0;

    memset(visit, false, sizeof visit);
    visit[0] = true;
}

int prim() {

    int total = 0;

    for (int i = 1; i < n; ++i) {

        int t = 8, k;

        for (int j = 1; j < n; ++j) {
            if (!visit[j] && dist[j] < t) {
                t = dist[j];
                k = j;
            }
        }

        visit[k] = true;
        total += t;

        for (int j = 1; j < n; ++j) {
            if (!visit[j] && map[k][j] < dist[j]) {
                dist[j] = map[k][j];
            }
        }
    }

    return total;
}

int main() {

    freopen("../a.in", "r", stdin);

    while (~scanf("%d", &n) && n != 0) {
        for (int i = 0; i < n; ++i) {
            scanf("%s", types[i]);
        }

        init();
        printf("The highest possible quality is 1/%d.\n", prim());
    }

    return 0;
}
