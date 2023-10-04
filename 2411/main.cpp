#include <iostream>

using namespace std;

#define LL long long

const int N = 11;
LL f[2][1 << N];
int n, m;

int main() {

    freopen("../a.in", "r", stdin);

    while (scanf("%d %d", &n, &m) && !(n == 0 && m == 0)) {
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        int t = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {

                t = 1 - t;
                memset(f[t], 0, sizeof f[t]);

                for (int s = 0; s < 1 << m; ++s) {
                    if (f[1 - t][s]) {
                        if (j != m - 1 && (!(s >> j & 3))) f[t][s | 1 << (j + 1)] += f[1 - t][s];  // 横放
                        f[t][s ^ 1 << j] += f[1 - t][s];  // 竖放或不放
                    }
                }
            }
        }
        printf("%lld\n", f[t][0]);
    }

}