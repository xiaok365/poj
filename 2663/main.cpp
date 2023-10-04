#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);
    int n;

    int f[31] = {0};
    f[0] = 1, f[2] = 3;

    for (int i = 4; i < 31; ++i) {
        if ((i & 1) == 0) {
            f[i] += f[i - 2] * 3;
            for (int j = 4; j <= i; j = j + 2) {
                f[i] += f[i - j] * 2;
            }
        }
    }

    while (scanf("%d", &n) && n != -1) {
        printf("%d\n", f[n]);
    }
    return 0;
}
