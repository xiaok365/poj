#include <iostream>

using namespace std;

#define MAXN 1025

int f[MAXN][MAXN] = {0}, n;

int lowbit(int x) {
    return x & -x;
}

void update(int x, int y, int value) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= n; j += lowbit(j)) {
            f[i][j] += value;
        }
    }
}

int query(int x, int y) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            ans += f[i][j];
        }
    }
    return ans;
}

int main() {
    freopen("../a.in", "r", stdin);
    int op;
    while (scanf("%d", &op) && op != 3) {
        switch (op) {
            case 0:
                scanf("%d", &n);
                break;
            case 1:
                int i, j, value;
                scanf("%d %d %d", &i, &j, &value);
                update(i + 1, j + 1, value);
                break;
            case 2:
                int l, b, r, t;
                scanf("%d %d %d %d", &l, &b, &r, &t);
                printf("%d\n", query(r + 1, t + 1) + query(l, b) - query(r + 1, b) - query(l, t + 1));
                break;
            default:;
        }
    }
    return 0;
}