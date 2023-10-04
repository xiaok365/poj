#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);
    int m, n, a, b;

    while (scanf("%d %d", &m, &n) && !(m == 0 && n == 0)) {
        m++;
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &a, &b);
            m -= b - a + 1;
        }
        printf("%d\n", m);
    }

    return 0;
}
