#include <iostream>

#define MAX_N 5001
int n, m, x1, y1, x2, y2;

struct Node {
    int u, l;
};

Node board[MAX_N];

struct Point {
    int x, y;

    Point() : x(0), y(0) {}
};

int cross(Node &a, Point &c) {
    return (a.u - a.l) * (c.y - y2) - (c.x - a.l) * (y1 - y2);
}

int main() {

    freopen("../a.in", "r", stdin);

    while (scanf("%d %d %d %d %d %d", &n, &m, &x1, &y1, &x2, &y2) == 6) {

        for (int i = 0; i < n; ++i) scanf("%d %d", &board[i].u, &board[i].l);

        int ans[MAX_N] = {0};

        for (int i = 0; i < m; ++i) {
            Point c;
            scanf("%d %d", &c.x, &c.y);

            int l = 0, r = n;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (cross(board[mid], c) >= 0) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            ans[l]++;
        }

        for (int i = 0; i <= n; ++i) {
            printf("%d: %d\n", i, ans[i]);
        }
        printf("\n");
    }

    return 0;
}
