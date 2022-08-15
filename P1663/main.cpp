#include <iostream>

int main() {
    freopen("../a.in", "r", stdin);
    int n, x, y;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &x, &y);
        if (x - y == 0 || x - y == 2) {
            printf("%d\n", 2 * x - x % 2 - (x - y));
        } else {
            printf("No Number\n");
        }
    }
    return 0;
}
