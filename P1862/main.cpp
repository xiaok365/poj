#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAX_N 101

int main() {

    freopen("../a.in", "r", stdin);

    int n;
    double a[MAX_N];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%lf", &a[i]);
    sort(a, a + n);

    double ans = a[n - 1];

    for (int i = n - 2; i >= 0; --i) {
        ans = 2 * sqrt(ans * a[i]);
    }

    printf("%.3lf", ans);

    return 0;
}
