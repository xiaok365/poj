#include <iostream>

struct Point {
    int x, y;

    Point() {}

    Point(int x, int y) : x(x), y(y) {}
};

int cross(Point &a, Point &b) {
    return a.x * b.y - a.y * b.x;
}

int det(int x1, int y1, int x2, int y2) {
    return x1 * y2 - x2 * y1;
}

int cross(Point &a, Point &b, Point &c) {
    return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

int main() {

    freopen("../a.in", "r", stdin);

    int n;
    Point a, b, c, d;
    scanf("%d", &n);

    printf("INTERSECTING LINES OUTPUT\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d %d %d %d %d", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);
        Point vector1, vector2;
        vector1 = Point(b.x - a.x, b.y - a.y);
        vector2 = Point(d.x - c.x, d.y - c.y);
        // parallel
        if (cross(vector1, vector2) == 0) {
            // same line
            if (cross(a, b, c) == 0) {
                printf("LINE\n");
            } else {
                printf("NONE\n");
            }
        } else {
            int s1 = cross(a, b, c);
            int s2 = cross(a, b, d);
            double x = double(c.x * s2 - d.x * s1) / (s2 - s1);
            double y = double(c.y * s2 - d.y * s1) / (s2 - s1);
            printf("POINT %.2lf %.2lf\n", x, y);
        }
    }
    printf("END OF OUTPUT\n");

    return 0;
}
