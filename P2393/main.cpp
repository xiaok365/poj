#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);

    int n, s, c, y;
    scanf("%d %d", &n, &s);

    long long ans = 0;
    int last = 5001;

    for (int i = 0; i < n; ++i) {

        scanf("%d %d", &c, &y);
        last += s;
        if (c < last) last = c;
        ans += last * y;
    }

    printf("%lld", ans);

    return 0;
}
