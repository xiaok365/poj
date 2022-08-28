#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);

    int t, n;
    long long a[50];
    scanf("%d", &t);

    a[0] = 1;
    a[1] = 2;

    for (int i = 2; i < 46; ++i) {
        a[i] = a[i - 1] + a[i - 2];
    }

    for (int i = 0; i < t; ++i) {
        scanf("%d", &n);
        printf("Scenario #%d:\n%lld\n\n", i + 1, a[n]);
    }
    return 0;
}
