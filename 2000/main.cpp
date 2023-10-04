#include <iostream>

#define MAX_N 10001

int main() {

    freopen("../a.in", "r", stdin);

    int n, a[MAX_N], i = 1, j = 0, k = 0;
    a[0] = 0;

    while (i < MAX_N) {
        k++;
        j += k;
        while (i <= j && i < MAX_N) {
            a[i] = k + a[i - 1];
            i++;
        }
    }

    while (scanf("%d", &n) && n != 0) {
        printf("%d %d\n", n, a[n]);
    }


    return 0;
}
