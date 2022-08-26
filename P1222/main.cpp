#include <iostream>

#define MAX_N 5
#define MAX_M 6

#define  N 31
int a[N][N];

void init() {

    memset(a, 0, sizeof a);
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_M; ++j) {
            int t = i * 6 + j;
            a[t][t] = 1;
            if (i > 0) a[t - 6][t] = 1;
            if (i < 4) a[t + 6][t] = 1;
            if (j > 0) a[t - 1][t] = 1;
            if (j < 5) a[t + 1][t] = 1;
        }
    }

    for (int i = 0; i < 30; ++i) scanf("%d", &a[i][30]);
}

void swap(int &s, int &t) {
    int tmp = s;
    s = t;
    t = tmp;
}

void gauss(int n) {
    //枚举列
    int r = 0, c = 0;
    for (; c < n; c++) {
        int t = r;
        for (int i = r; i < n; i++)
            if (a[i][c]) {
                t = i;
                break;
            }
        if (!a[t][c]) continue;
        //交换两行
        for (int i = c; i <= n; i++) swap(a[t][i], a[r][i]);
        //从 r + 1行开始消零
        for (int i = r + 1; i < n; i++)
            if (a[i][c])
                for (int j = c; j <= n; j++) a[i][j] ^= a[r][j];
        r++;
    }
    //判断是否有解
    if (r < n) {
        for (int i = r; i < n; i++)
            if (a[i][n]) {
                printf("no solution\n");
                break;
            }
        printf("multi solution\n");
    }

    //将所有行消掉0
    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++)
            a[i][n] ^= a[i][j] & a[j][n];
}

int main() {

    freopen("../a.in", "r", stdin);

    int n;
    scanf("%d", &n);
    for (int t = 0; t < n; ++t) {

        init();
        printf("PUZZLE #%d\n", t + 1);

        gauss(30);
        for (int i = 0; i < 30; i++) {
            printf("%d", a[i][30]);
            if ((i + 1) % 6 == 0) printf("\n"); else printf(" ");
        }
    }

    return 0;
}
