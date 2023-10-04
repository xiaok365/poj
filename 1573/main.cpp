#include <iostream>

#define MAX_N 100

const int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

int n, m;

bool legal(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int to(char d) {
    switch (d) {
        case 'E':
            return 0;
        case 'S':
            return 1;
        case 'W':
            return 2;
        default:
            return 3;
    }
}

int main() {
    freopen("../a.in", "r", stdin);

    int s;
    int visit[MAX_N][MAX_N];
    char map[MAX_N][MAX_N];
    while (scanf("%d %d %d", &n, &m, &s) && !(n == 0 && m == 0 && s == 0)) {
        for (int i = 0; i < n; ++i) scanf("%s", map[i]);
        memset(visit, 0xff, sizeof visit);
        int x = 0, y = s - 1, step = 0;
        bool loop = false;
        while (legal(x, y)) {
            if (visit[x][y] >= 0) {
                loop = true;
                printf("%d step(s) before a loop of %d step(s)\n", visit[x][y], step - visit[x][y]);
                break;
            }
            visit[x][y] = step++;
            int d = to(map[x][y]);
            x += dir[d][0];
            y += dir[d][1];
        }

        if (!loop) printf("%d step(s) to exit\n", step);
    }
    return 0;
}
