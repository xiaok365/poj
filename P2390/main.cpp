#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);

    double r, m;
    int y;
    scanf("%lf %lf %d", &r, &m, &y);

    for (int i = 0; i < y; ++i) {
        m = m * ((100 + r) / 100);
    }

    printf("%.0lf", m - 0.5);
    return 0;
}
