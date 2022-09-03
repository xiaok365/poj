#include <iostream>

int main() {

    freopen("../a.in", "r", stdin);
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = -(n - 1), v;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v);
            ans += v;
        }
        printf("%d\n", ans);
    }
    return 0;
}
