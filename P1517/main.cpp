#include <iostream>

using namespace std;

double fac(int x) {
    double ret = 1;
    for (int i = 1; i <= x; ++i) {
        ret *= i;
    }
    return ret;
}

int main() {

    printf("n e\n");
    printf("- -----------\n");
    for (int i = 0; i <= 9; ++i) {
        double ans = 0;
        for (int j = 0; j <= i; ++j) {
            ans += 1 / fac(j);
        }
        if (i <= 1) {
            printf("%d %.0f\n", i, ans);
        } else if (i == 2) {
            printf("%d %.1f\n", i, ans);
        } else {
            printf("%d %.9f\n", i, ans);
        }
    }
    return 0;
}