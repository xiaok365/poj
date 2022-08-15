#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);

    int n;
    while (scanf("%d", &n) && n != -1) {

        int ans = 0, speed, now, last = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &speed, &now);
            ans += speed * (now - last);
            last = now;
        }
        printf("%d miles\n", ans);
    }
    return 0;
}
