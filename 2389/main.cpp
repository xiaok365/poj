#include <iostream>

#define LEN 41

char *multiply(const char a[], int lena, const char b[], int lenb) {

    int c[LEN * 2] = {0};
    int lenc = lena + lenb;

    for (int i = 0; i < lena; ++i) {
        for (int j = 0; j < lenb; ++j) {
            int t = (a[lena - i - 1] - '0') * (b[lenb - j - 1] - '0');
            c[i + j] += t;
            c[i + j + 1] += c[i + j] / 10;
            c[i + j] %= 10;
        }
    }

    while (c[lenc] == 0) lenc--;

    static char ans[LEN * 2] = "";
    for (int i = 0; i <= lenc; ++i) ans[i] = c[lenc - i] + '0';

    return ans;
}

int main() {

    freopen("../a.in", "r", stdin);

    char a[LEN], b[LEN];
    scanf("%s %s", a, b);
    printf("%s", multiply(a, strlen(a), b, strlen(b)));

    return 0;
}
