#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);

    int t;
    long long n, m, ans;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {

        scanf("%lld %lld", &n, &m);
        ans = (n + m) * (m - n + 1) >> 1;
        printf("Scenario #%d:\n%lld\n\n", i + 1, ans);
    }

    return 0;
}
