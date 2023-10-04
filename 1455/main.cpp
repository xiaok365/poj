#include <iostream>

int calc(int x) {
    return x * (x - 1) / 2;
}

int main() {
    freopen("../a.in", "r", stdin);
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int x = n / 2, ans;
        if (n & 1) {
            ans = calc(x) + calc(x + 1);
        } else {
            ans = calc(x) * 2;
        }
        printf("%d\n", ans);
    }
    return 0;
}
