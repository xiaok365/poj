#include <iostream>

using namespace std;

int main() {
    freopen("../a.in", "r", stdin);
    int n, s, t;
    while (scanf("%d", &n) && n) {
        int ans = 0x7fffffff;
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &s, &t);
            if (t < 0) continue;
            int tt = 16200 / s + t;
            if (16200 % s) tt++;
            ans = ans > tt ? tt : ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}
