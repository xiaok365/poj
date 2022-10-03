#include <iostream>

int cube(int x) {
    return x * x * x;
}

int main() {
    freopen("../a.in", "r", stdin);
    int n;
    scanf("%d", &n);

    for (int a = 2; a <= n; ++a) {
        for (int b = 2; b <= a; ++b) {
            for (int c = b + 1; c <= a; ++c) {
                for (int d = c + 1; d <= a; ++d) {
                    if (cube(a) == cube(b) + cube(c) + cube(d)) {
                        printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, d);
                    }
                }
            }
        }
    }

    return 0;
}
