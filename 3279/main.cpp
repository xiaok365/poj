#include <iostream>

#define MAX_N 1000

int n, m, a[MAX_N][MAX_N];

void init() {

    scanf("%d %d", &n, &m);
    memset(a, 0, sizeof a);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int t = i * m + j;
            a[t][t] = 1;
            if (i > 0) a[t - m][t] = 1;
            if (i < n - 1) a[t + m][t] = 1;
            if (j > 0) a[t - 1][t] = 1;
            if (j < m - 1) a[t + 1][t] = 1;
            scanf("%d", &a[t][n * m]);
        }
    }
}

void swap(int &s, int &t) {
    int tmp = s;
    s = t;
    t = tmp;
}

int gauss(int nm) {

    int r = 0, c = 0;
    for (; c < nm; ++c) {

        int t = r;
        for (int i = r; i < nm; ++i) {
            if (a[i][c]) {
                t = i;
                break;
            }
        }

        if (!a[t][c]) continue;

        // 交换两行
        for (int i = c; i <= nm; ++i) swap(a[t][i], a[r][i]);

        // 消元
        for (int i = r + 1; i < nm; ++i) {
            if (a[i][c]) {
                for (int j = c; j <= nm; ++j) {
                    a[i][j] ^= a[r][j];
                }
            }
        }
        r++;
    }

    // 是否有解
    if (r < nm) {
        for (int i = r; i < nm; ++i) {
            if (a[i][nm]) return 1;
        }
    }

    // 化简
    for (int i = nm - 1; i >= 0; --i) {
        for (int j = i + 1; j < nm; ++j) {
            a[i][nm] ^= a[i][j] & a[j][nm];
        }
    }

    return 0;
}

int main() {

    freopen("../a.in", "r", stdin);

    init();

    int ret = gauss(n * m);

    if (ret) {
        printf("IMPOSSIBLE");
    } else {
        for (int i = 0; i < n * m; ++i) {
            printf("%d", a[i][n * m]);
            if ((i + 1) % m == 0) printf("\n"); else printf(" ");
        }
    }

    return 0;
}
