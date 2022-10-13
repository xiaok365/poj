#include <iostream>
#include <map>

#define rep(i, a, b) for (int i=a;i<=b;i++)
#define MAX_N 25000001
#define FIX 12500000

#define ZERO 50
#define RIGHT 100

using namespace std;

int a[5];
short b[MAX_N] = {0};

int cube(int i, int x) {
    return a[i] * x * x * x;
}

int main() {
    freopen("../a.in", "r", stdin);

    rep(i, 0, 4) scanf("%d", &a[i]);
    rep(i, 0, RIGHT) {
        if (i == ZERO)continue;
        rep(j, 0, RIGHT) {
            if (j == ZERO)continue;
            int t = cube(0, i - ZERO) + cube(1, j - ZERO);
            b[t + FIX]++;
        }
    }

    int ans = 0;
    rep(i, 0, RIGHT) {
        if (i == ZERO)continue;
        rep(j, 0, RIGHT) {
            if (j == ZERO)continue;
            rep(k, 0, RIGHT) {
                if (k == ZERO)continue;
                int t = -cube(2, i - ZERO) - cube(3, j - ZERO) - cube(4, k - ZERO);
                if (t + FIX < 0 || t + FIX >= MAX_N) continue;
                ans += b[t + FIX];
            }
        }
    }

    printf("%d", ans);
    return 0;
}
