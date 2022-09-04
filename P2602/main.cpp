#include <iostream>

#define MAX_N 1000001

int main() {

    freopen("../a.in", "r", stdin);

    char a[MAX_N], b, c;
    int n;

    scanf("%d", &n), getchar();
    for (int i = 0; i < n; ++i) {
        b = getchar(), getchar();
        c = getchar(), getchar();
        a[i] = b + c - 96;
    }
    for (int i = n - 1; i >= 0; --i) {
        a[i - 1] += a[i] / 10;
        a[i] = (a[i] % 10) + '0';
    }
    printf("%s", a);
    return 0;
}
