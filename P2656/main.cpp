#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);
    int n;

    while (scanf("%d", &n) && n != 0) {
        int min = 0, j = 0, a, b;
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &a, &b);
            if (a + b > min) {
                min = a + b;
                j = i + 1;
            }
        }
        if (min <= 8) printf("0\n"); else printf("%d\n", j);
    }
    return 0;
}
