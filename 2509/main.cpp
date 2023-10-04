#include <iostream>

int main() {
    freopen("../a.in", "r", stdin);

    int n, k;
    while (~scanf("%d %d", &n, &k)) {
        int ans = n;
        while (n >= k) {
            ans += n / k;
            n = n / k + n % k;
        }
        printf("%d\n", ans);
    }
    return 0;
}
