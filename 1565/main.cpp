#include <iostream>

#define MAX_N 100
#define LL long long

int main() {

    freopen("../a.in", "r", stdin);

    char st[MAX_N];
    LL a[32];

    a[0] = 1;
    for (int i = 1; i < 32; ++i) a[i] = a[i - 1] * 2;

    while (scanf("%s", st) && st[0] != '0') {
        LL ans = 0, len = strlen(st);
        for (int i = len - 1; i >= 0; --i) {
            ans += (st[i] - '0') * (a[len - i] - 1);
        }
        printf("%lld\n", ans);
    }

    return 0;
}
