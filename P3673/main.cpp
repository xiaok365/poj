#include <iostream>

#define MAX_N 11

int main() {

    freopen("../a.in", "r", stdin);

    char a[MAX_N], b[MAX_N];

    scanf("%s %s", a, b);

    int lena = strlen(a), lenb = strlen(b), ans = 0;

    for (int i = 0; i < lena; ++i) {
        for (int j = 0; j < lenb; ++j) {
            ans += (a[i] - '0') * (b[j] - '0');
        }
    }
    printf("%d", ans);

    return 0;
}
