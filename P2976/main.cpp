#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 1001

int n, m, x[MAX_N], y[MAX_N];

bool check(double mid) {
    double z[MAX_N];
    for (int i = 0; i < n; ++i) {
        z[i] = 1.0 * x[i] - 1.0 * y[i] * mid;
    }
    sort(z, z + n);
    double tot = 0;
    for (int i = n - 1; i >= m; --i) tot += z[i];
    return tot >= 0;
}

int main() {
    freopen("../a.in", "r", stdin);

    while (scanf("%d %d", &n, &m) && !(n == 0 && m == 0)) {
        for (int i = 0; i < n; ++i) scanf("%d", &x[i]);
        for (int i = 0; i < n; ++i) scanf("%d", &y[i]);
        double l = 0, r = 1.0;
        while (r - l > 1e-5) {
            double mid = (l + r) / 2;
            if (check(mid)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        printf("%.0f\n", l * 100);
    }
    return 0;
}
