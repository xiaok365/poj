#include <iostream>
#include <algorithm>

int main() {

    freopen("../a.in", "r", stdin);
    int n, a[10000];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    std::sort(a, a + n);

    printf("%d", a[n / 2]);

    return 0;
}
