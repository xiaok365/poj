#include <iostream>

int map[101][101] = {0};

void set(int x, int y, int l, int d) {
    for (int i = x; i < x + l; ++i) {
        for (int j = y; j < y + l; ++j) {
            map[i][j] = d;
        }
    }
}

int query(int x, int y, int l) {
    int ans = 0;
    for (int i = x; i < x + l; ++i) {
        for (int j = y; j < y + l; ++j) {
            ans += map[i][j];
        }
    }
    return ans;
}

int main() {
    freopen("../a.in", "r", stdin);
    int n, x, y, l;
    char st[10];
    scanf("%d", &n);
    for (int k = 0; k < n; ++k) {
        scanf("%s %d %d %d", st, &x, &y, &l);
        switch (st[0]) {
            case 'B':
                set(x, y, l, 1);
                break;
            case 'W':
                set(x, y, l, 0);
                break;
            default:
                printf("%d\n", query(x, y, l));
                break;
        }
    }
    return 0;
}
