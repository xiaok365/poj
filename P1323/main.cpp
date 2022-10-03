#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 100

int main() {

    freopen("../a.in", "r", stdin);

    int n, m, a[MAX_N], cases = 0;
    while (scanf("%d %d", &n, &m) && !(n == 0 && m == 0)) {
        for (int i = 0; i < m; ++i) scanf("%d", &a[i]);
        sort(a, a + m);
        int ans = 0, cnt = 0;
        a[m] = n * m + 1;
        for (int i = m - 1; i >= 0; --i) {
            cnt += a[i + 1] - a[i] - 1;
            if (cnt == 0) {
                ans++;
            } else {
                cnt--;
            }
        }
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
