#include <iostream>

#define MAX_N 15

struct Point {
    int x, y;

    Point() {}

    Point(int x, int y) : x(x), y(y) {}
};

struct Line {
    Point p1, p2;
};

Line line[MAX_N];
int father[MAX_N];

int det(int x1, int y1, int x2, int y2) {
    return x1 * y2 - x2 * y1;
}

int cross(Point &a, Point &b, Point &c) {
    return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

int sign(int x) {
    if (x == 0) return 0;
    return x > 0 ? 1 : -1;
}

int dotdet(int x1, int y1, int x2, int y2) {
    return x1 * x2 + y1 * y2;
}

int dot(Point &a, Point &b, Point &c) {
    return dotdet(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

int between(Point &a, Point &b, Point &c) {
    return sign(dot(a, b, c));
}

int find_father(int x) {
    int root = x;
    while (father[root] >= 0) {
        root = father[root];
    }
    while (x != root) {
        int t = father[x];
        father[x] = root;
        x = t;
    }
    return root;
}

void union_set(int x, int y) {
    int root_x = find_father(x);
    int root_y = find_father(y);
    if (root_x == root_y) return;
    int num = father[root_x] + father[root_y];
    if (father[root_x] > father[root_y]) {
        father[root_x] = root_y;
        father[root_y] = num;
    } else {
        father[root_y] = root_x;
        father[root_x] = num;
    }
}

void init(int n) {
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        line[i].p1 = Point(x1, y1);
        line[i].p2 = Point(x2, y2);
    }
    memset(father, 0xff, sizeof father);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int d1 = sign(cross(line[i].p1, line[i].p2, line[j].p1));
            int d2 = sign(cross(line[i].p1, line[i].p2, line[j].p2));
            int d3 = sign(cross(line[j].p1, line[j].p2, line[i].p1));
            int d4 = sign(cross(line[j].p1, line[j].p2, line[i].p2));
            // 规范相交
            if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) {
                union_set(i, j);
            }
            // 非规范相交
            if (d1 == 0 && between(line[j].p1, line[i].p1, line[i].p2) <= 0 ||
                d2 == 0 && between(line[j].p2, line[i].p1, line[i].p2) <= 0 ||
                d3 == 0 && between(line[i].p1, line[j].p1, line[j].p2) <= 0 ||
                d4 == 0 && between(line[i].p2, line[j].p1, line[j].p2) <= 0) {
                union_set(i, j);
            }
        }
    }
}

void solve() {
    int from, to;
    while (scanf("%d %d", &from, &to) && !(from == 0 && to == 0)) {
        if (find_father(from - 1) == find_father(to - 1)) {
            printf("CONNECTED\n");
        } else {
            printf("NOT CONNECTED\n");
        }
    }
}

int main() {
    freopen("../a.in", "r", stdin);
    int n;
    while (scanf("%d", &n) && n) {
        init(n);
        solve();
    }
    return 0;
}
