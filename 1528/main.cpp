#include <iostream>

int main() {
    freopen("../a.in", "r", stdin);
    int n;
    printf("PERFECTION OUTPUT\n");
    while (scanf("%d", &n) && n > 0) {
        int sum = 1;
        if (n == 1) sum = 0;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                sum += i + n / i;
            }
        }
        if (sum > n) {
            printf("%5d  ABUNDANT\n", n);
        } else if (sum < n) {
            printf("%5d  DEFICIENT\n", n);
        } else {
            printf("%5d  PERFECT\n", n);
        }
    }
    printf("END OF OUTPUT\n");
    return 0;
}
